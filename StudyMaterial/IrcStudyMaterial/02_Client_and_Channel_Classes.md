# ft_irc — Client & Channel Classes

This document details the implementation of the core data models: the `Client` and `Channel` classes. These components are defined in the `inc/` folder and implemented in `src/Client.cpp` and `src/Channel.cpp`.

---

## 1. The Client Class (`Client.hpp` & `Client.cpp`)

The `Client` class represents a connected user, storing their connection metadata, credentials, and state flags.

### Class Member Variables
```cpp
class Client {
    private:
        int         _fd;            // Socket file descriptor
        std::string _ipAddress;     // Client IP address
        std::string _buffer;        // Temp buffer for reading fragments
        std::string _nickname;      // Registered nickname
        std::string _username;      // Registered username
        bool        _isRegistered;  // Registration state
        bool        _hasPassword;   // Has provided password
        bool        _hasUsername;   // Has provided username
        bool        _hasNickname;   // Has provided nickname
```

### Key Methods

#### [Client Constructor](file:///c:/42AD/staff-evaluation/irc/src/Client.cpp#L6-L10)
* Sets the client's socket descriptor and IP address, clears strings, and initializes state flags (`_isRegistered`, `_hasPassword`, etc.) to `false`.

#### [appendToBuffer](file:///c:/42AD/staff-evaluation/irc/src/Client.cpp#L103-L106) & [clearBuffer](file:///c:/42AD/staff-evaluation/irc/src/Client.cpp#L108-L111)
* **What it is for:** Manages read fragment integration.
* **Why it is needed:** Data packet fragmentation. If a client sends a message in parts, the parser appends it to the buffer until a newline `\n` is found.

#### [sendMessage](file:///c:/42AD/staff-evaluation/irc/src/Client.cpp#L113-L118)
* **What it is for:** Sends a message to the client socket.
* **Why it is needed:** Wraps socket output operations.
* **How it works:** Appends the required IRC suffix **`\r\n`** to the end of the message string and calls `send` to transmit it:
  ```cpp
  std::string msg = message + "\r\n";
  send(_fd, msg.c_str(), msg.length(), 0);
  ```

---

## 2. The Channel Class (`Channel.hpp` & `Channel.cpp`)

The `Channel` class represents a chat room, managing the lists of members, operators, invitations, and channel modes.

### Class Member Variables
```cpp
class Channel {
    private:
        std::string        _name;            // Channel name (starts with # or &)
        std::set<Client*>  _clients;         // Set of members
        std::set<Client*>  _operators;       // Set of channel operators (ops)
        std::set<Client*>  _invitedClients;  // Set of invited users
        std::string        _topic;           // Channel topic string
        std::string        _password;        // Channel key (mode +k)
        size_t             _userLimit;       // Max members limit (mode +l)
        bool               _inviteOnly;      // Invite-only flag (mode +i)
        bool               _topicRestricted; // Operator-only topic (mode +t)
```
* **Why `std::set` is used:** A set stores unique pointers and provides $O(\log n)$ insertion, search, and deletion, which is faster and cleaner than checking duplicates in a vector.

### Key Methods

#### [broadcast](file:///c:/42AD/staff-evaluation/irc/src/Channel.cpp#L67-L76)
* **What it is for:** Sends a message to all members of the channel.
* **Why it is needed:** Distributes chat messages, join/part notices, and mode changes.
* **How it works:** Iterates through `_clients`, calling `sendMessage()` on each client. The optional `exclude` parameter allows skipping the sender so they do not receive an echo of their own message.

#### [addClient](file:///c:/42AD/staff-evaluation/irc/src/Channel.cpp#L98-L102) & [removeClient](file:///c:/42AD/staff-evaluation/irc/src/Channel.cpp#L104-L109)
* **What it is for:** Manages channel membership.
* **How it works:**
  * `addClient`: Inserts the client into the `_clients` set and erases them from `_invitedClients` (consuming their invitation).
  * `removeClient`: Erases the client from `_clients`, `_operators`, and `_invitedClients` to ensure no dangling pointers remain if they leave the channel.

#### Mode Operations Getters/Setters
* Modifies configuration flags (`_inviteOnly`, `_topicRestricted`, `_password`, `_userLimit`) and queries status properties (such as `isOperator` or `isInvited`).

---

## Next Steps

Now let's trace the client connection sequence and the **Authentication Commands**.

👉 Proceed to [03_Authentication_Commands.md](./03_Authentication_Commands.md)
