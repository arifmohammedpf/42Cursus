# ft_irc — Evaluation Q&A Cheat Sheet

This document compiles the most common questions asked by 42 evaluators during the ft_irc defense, along with clear, technical, and accurate answers to help you explain the project successfully.

---

## 1. Networking & Socket Programming

### Q1: What is the difference between TCP and UDP?
* **Answer:**
  * **TCP (Transmission Control Protocol):** A connection-oriented protocol. It guarantees the delivery of packets in the correct order using sequence numbers, acknowledgments, and retransmissions. It is used for applications like IRC, HTTP, and SSH where data integrity is critical.
  * **UDP (User Datagram Protocol):** A connectionless protocol. It sends packets ("datagrams") without establishing a connection or verifying delivery. It has lower overhead and is faster, making it suitable for video streaming or gaming where occasional packet loss is acceptable.

### Q2: Why did you choose `poll()` instead of spawning a new thread for each client?
* **Answer:** Spawning a thread per client ("Thread-per-Connection" model) does not scale well. Each thread requires system resources (like stack memory) and introduces CPU overhead due to context switching. Additionally, multi-threaded programs require complex synchronization (like mutexes) to prevent race conditions when accessing shared data like channel member lists.
* `poll()` implements **I/O Multiplexing**. It allows a single thread to monitor hundreds of socket descriptors simultaneously. The thread sleeps until the kernel alerts it of network activity, making the server highly efficient and thread-safe.

### Q3: What is the purpose of `fcntl(..., O_NONBLOCK)`?
* **Answer:** By default, socket functions (like `accept`, `recv`, `send`) are blocking. If a socket is blocking and we call `recv` when no data is available, the thread halts, freezing the entire server. Setting sockets to non-blocking mode ensures these functions return immediately with an error (like `EWOULDBLOCK` or `EAGAIN`) if they cannot complete, allowing the event loop to continue processing other clients.

### Q4: What does `setsockopt(..., SO_REUSEADDR, ...)` do?
* **Answer:** When a TCP socket is closed, the port remains bound in the kernel for a few minutes in a `TIME_WAIT` state to ensure any late packets are discarded. This prevents the server from restarting on that port immediately. `SO_REUSEADDR` tells the kernel to allow binding to the port even if it is in a `TIME_WAIT` state, enabling instant server restarts.

---

## 2. Buffer Management & Robustness

### Q5: How does the server handle message fragmentation (where a command is split across multiple TCP packets)?
* **Answer:** TCP is a stream-based protocol, not a message-based protocol. It does not guarantee that a single client write corresponds to a single server read.
* To handle this, the server maintains an internal `_buffer` string inside each `Client` object. When `recv` reads data, the server appends it to the client's buffer. It then searches for the `\n` delimiter. If found, it extracts the command up to the newline, processes it, and clears that portion from the buffer. If no newline is found, the server leaves the data in the buffer and waits for the next read event.

### Q6: How does the server handle carriage return (`\r`) differences between Windows and Linux clients?
* **Answer:** Different clients terminate lines differently: Linux uses `\n` (Line Feed), while Windows/IRC specifications use `\r\n` (Carriage Return + Line Feed).
* Our server splits messages by `\n` first, then checks if the resulting string ends with `\r`. If so, it erases the `\r` character before parsing the command parameters:
  ```cpp
  if (!message.empty() && message[message.length() - 1] == '\r') {
      message.erase(message.length() - 1);
  }
  ```

---

## 3. IRC Protocol Details

### Q7: What is the difference between `PRIVMSG` and `NOTICE`?
* **Answer:** Both route messages to users or channels, but they differ in error handling:
  * `PRIVMSG` is used for user chat and returns numeric error replies (like `401 ERR_NOSUCHNICK`) if the target is invalid.
  * `NOTICE` is used for system messages. It **must never** return error replies. This rule prevents infinite message loops between automated bots or servers.

### Q8: What happens when the last client leaves a channel?
* **Answer:** To prevent memory leaks, when a client leaves a channel (via `PART`, `KICK`, or `QUIT`), the server checks if the channel's membership list is empty. If so, it deletes the `Channel` object from the heap and erases its entry from the server's `_channels` map.

### Q9: How does the server handle unexpected terminations (e.g. client crashes or loses internet)?
* **Answer:** If a client terminates unexpectedly, the server's `recv` call for that socket descriptor returns `0` (orderly shutdown) or a negative value (connection reset). The server detects this, calls `disconnectClient`, broadcasts a `QUIT` message to their channels, closes the socket, and frees the client's memory.
