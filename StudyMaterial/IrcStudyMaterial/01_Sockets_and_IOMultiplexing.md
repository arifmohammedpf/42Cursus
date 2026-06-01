# ft_irc — Sockets & I/O Multiplexing

This document explains the networking layer of the server, detailing the socket configurations and the event loop multiplexing implemented in [Server.cpp](file:///c:/42AD/staff-evaluation/irc/src/Server.cpp).

---

## 1. Socket Setup & Bind (`Server::Server`)

The constructor initializes a non-blocking TCP socket to listen for incoming connections.

```cpp
Server::Server(int port, const std::string &password) : _port(port), _password(password) {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0)
        throw std::runtime_error("Failed to create socket");
```
* **`socket()`**: Creates a communication endpoint.
  * `AF_INET`: Specifies IPv4 network protocols.
  * `SOCK_STREAM`: Specifies a two-way, connection-based byte stream (TCP).
  * `0`: Chooses the default protocol for TCP.

```cpp
    int opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("Failed to set SO_REUSEADDR");
```
* **`setsockopt(..., SO_REUSEADDR, ...)`**: Configures socket behaviors.
  * **Why it is needed:** When the server is shut down, its port remains bound in the kernel for a few minutes in a `TIME_WAIT` state, preventing the server from restarting on the same port immediately. Setting `SO_REUSEADDR` allows immediate rebinding to the port, which is crucial for development and rapid testing.

```cpp
    if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Failed to set non-blocking mode");
```
* **`fcntl(..., F_SETFL, O_NONBLOCK)`**: Sets the file descriptor status flags.
  * **Why it is needed:** By default, socket calls (like `accept`, `recv`, `send`) are blocking. If no client is connecting, `accept` will hang the entire thread, halting the server. Configuring the socket to non-blocking mode ensures that if an operation cannot complete immediately, it returns immediately with an error (like `EWOULDBLOCK` or `EAGAIN`) instead of blocking, allowing the poll loop to continue.

```cpp
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        throw std::runtime_error("Failed to bind socket");
```
* **`bind()`**: Assigns the address and port details to the socket file descriptor.
  * `htons(_port)`: Converts the port integer from host byte order to network byte order (Big-Endian).
  * `INADDR_ANY`: Binds the socket to all available network interfaces on the host.

```cpp
    if (listen(_serverSocket, SOMAXCONN) < 0)
        throw std::runtime_error("Failed to listen on socket");
```
* **`listen()`**: Marks the socket as a passive listener to accept incoming connections.
  * `SOMAXCONN`: Sets the maximum size of the backlog queue for pending connections.

```cpp
    struct pollfd pfd;
    pfd.fd = _serverSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollfds.push_back(pfd);
}
```
* Registers the listening socket in the `_pollfds` array to monitor for read events (`POLLIN`).

---

## 2. The Multiplexing Loop (`Server::start`)

The main event loop monitors socket events, processes connections, and reads client data.

```cpp
void Server::start() {
    while (g_running) {
        int pollCount = poll(&_pollfds[0], _pollfds.size(), -1);
```
* **`poll()`**: Blocks execution until one or more monitored sockets have pending activity.
  * `&_pollfds[0]`: A pointer to the array of `pollfd` structures.
  * `_pollfds.size()`: The number of descriptors to monitor.
  * `-1`: Wait indefinitely (blocks until an event occurs).
* If a signal (like `SIGINT` from Ctrl+C) occurs, `poll` fails and returns `-1`. The signal handler sets `g_running = false`, breaking the loop and initiating shutdown.

### Distinguishing Events
The loop iterates through `_pollfds`:
```cpp
        for (size_t i = 0; i < _pollfds.size(); i++) {
            if (_pollfds[i].revents & POLLIN) {
                if (_pollfds[i].fd == _serverSocket) {
                    acceptConnection();
                } 
```
* If the event is on the `_serverSocket`, a new client is trying to connect. The server calls `acceptConnection()`.
* Otherwise, the event is on a client socket. The server reads incoming data from that client.

---

## 3. Accepting Connections & Reading Packets

### [acceptConnection](file:///c:/42AD/staff-evaluation/irc/src/Server.cpp#L87-L109)
* **What it is for:** Accepts an incoming client connection.
* **How it works:**
  1. Calls `accept()` to extract the next connection from the listening socket's backlog queue, generating a new socket descriptor (`clientSocket`).
  2. Sets `clientSocket` to non-blocking mode: `fcntl(clientSocket, F_SETFL, O_NONBLOCK)`.
  3. Registers the new client in the `_pollfds` vector to monitor it for incoming data (`POLLIN`).
  4. Resolves the client IP address using `inet_ntoa(clientAddr.sin_addr)`.
  5. Instantiates a new `Client` object and stores it in the `_clients` map: `_clients[clientSocket] = new Client(...)`.

### Reading & Aggregating Buffers
Inside the client loop of `Server::start`:
```cpp
                    int fd = _pollfds[i].fd;
                    char buffer[1024];
                    int bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
```
* **`recv()`**: Reads bytes from the client socket.
* **Handling Disconnection:** If `bytes <= 0`, it indicates the client disconnected (or a read error occurred). The server calls `disconnectClient` to free resources.
* **Buffer Processing:**
  1. Null-terminates the buffer: `buffer[bytes] = '\0'`.
  2. Appends the data to the client's internal string buffer: `_clients[fd]->appendToBuffer(buffer)`.
  3. Scans for the newline character (`\n`) which acts as the command delimiter:
     ```cpp
     while ((pos = _clients[fd]->getBuffer().find('\n')) != std::string::npos) {
         std::string message = _clients[fd]->getBuffer().substr(0, pos);
     ```
  4. Strips any trailing carriage return (`\r`) to isolate the command:
     ```cpp
     if (!message.empty() && message[message.length() - 1] == '\r') {
         message.erase(message.length() - 1);
     }
     ```
  5. Passes the message to `handleMessage()`.
  6. Removes the processed command from the buffer, leaving any remaining partial data in the buffer for the next `recv`.

---

## 4. Disconnecting Clients (`Server::disconnectClient`)

### [disconnectClient](file:///c:/42AD/staff-evaluation/irc/src/Server_utils.cpp#L39-L75)
* **What it is for:** Safely shuts down a client connection and cleans up associated memory.
* **How it works:**
  1. Generates a standard `QUIT` broadcast message: `:nick!user@host QUIT :reason`.
  2. Iterates through all channels:
     - If the client is a member, broadcasts the `QUIT` message to all other channel members.
     - Removes the client from the channel's sets.
     - If a channel becomes empty, deletes it from the `_channels` registry.
  3. Erases the client's structure from the `_pollfds` vector to stop monitoring it.
  4. Closes the socket file descriptor: `close(fd)`.
  5. Deletes the heap-allocated `Client` object and erases it from the `_clients` map.

---

## Next Steps

Now let's examine the structure of the data models: the **Client** and **Channel** classes.

👉 Proceed to [02_Client_and_Channel_Classes.md](./02_Client_and_Channel_Classes.md)
