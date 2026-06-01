# ft_irc — Overview & Architecture

Welcome to the ft_irc Study Materials! This guide is designed to help you understand every aspect of the custom Internet Relay Chat (IRC) server codebase, from socket-level networking to IRC command parsing and client communication lifecycles.

---

## 1. What is ft_irc?

**ft_irc** is a C++ project at 42 where you build a fully functional **IRC Server** from scratch. The server implements the standard IRC protocol (specifically following **RFC 2812** specs) to allow multiple chat clients (such as HexChat, Irssi, or netcat) to connect, authenticate, create channels, join chat rooms, send private messages, and execute administrator commands.

---

## 2. Server Architecture and Lifecycle

The server runs on a single thread and processes events asynchronously. It does not spawn separate threads for each client. Instead, it uses **I/O Multiplexing** to manage all client descriptors in a single execution loop.

```
                              ft_irc Server Loop
                                      │
  1. Create Socket: Establish TCP listening socket.
                                      │
  2. Bind & Listen: Bind socket to port and configure backlog cue.
                                      │
  3. Non-blocking: Set O_NONBLOCK flag on the server descriptor.
                                      │
  4. Poll Loop (multiplexing):
     ┌──► Call poll() to wait for network activities.
     │      │
     │      ├──► Activity on Server Socket:
     │      │    Call accept() to verify connection.
     │      │    Configure new client socket to O_NONBLOCK.
     │      │    Push client fd into pollfd vector.
     │      │
     │      └──► Activity on Client Socket:
     │           Call recv() to fetch bytes into client buffer.
     │           If bytes <= 0: Disconnect client and close socket.
     │           If carriage return (\n) found:
     │             Extract message, strip trailing '\r', and route command.
     └───────────────────────────────────┘
```

---

## 3. Directory and Component Map

Here is how the codebase is organized:

* **`inc/`**
  * [Client.hpp](file:///c:/42AD/staff-evaluation/irc/inc/Client.hpp) — Client state container class header.
  * [Channel.hpp](file:///c:/42AD/staff-evaluation/irc/inc/Channel.hpp) — Channel/chat-room representation class header.
  * [Server.hpp](file:///c:/42AD/staff-evaluation/irc/inc/Server.hpp) — Main socket engine and command router class header.
  * [Replies.hpp](file:///c:/42AD/staff-evaluation/irc/inc/Replies.hpp) — Map of standard numeric replies and error codes (RFC 2812).
* **`src/`**
  * [main.cpp](file:///c:/42AD/staff-evaluation/irc/src/main.cpp) — Command line entry point, port verification, and signal handler.
  * [Server.cpp](file:///c:/42AD/staff-evaluation/irc/src/Server.cpp) — Sockets creation, `poll` loop, client acceptance, and string parser.
  * [Server_utils.cpp](file:///c:/42AD/staff-evaluation/irc/src/Server_utils.cpp) — Numeric replies formatters, registration checkers, and client disconnectors.
  * [Client.cpp](file:///c:/42AD/staff-evaluation/irc/src/Client.cpp) — Client variables, buffers, and socket writer implementation.
  * [Channel.cpp](file:///c:/42AD/staff-evaluation/irc/src/Channel.cpp) — Clients list management, modes configuration, and broadcasting implementation.
  * [CommandsAuth.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsAuth.cpp) — `PASS`, `NICK`, `USER` commands.
  * [CommandsChannel.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsChannel.cpp) — `JOIN`, `PART`, `TOPIC`, `MODE` commands.
  * [CommandsChat.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsChat.cpp) — `PRIVMSG`, `NOTICE` message deliverers.
  * [CommandsOper.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsOper.cpp) — `KICK`, `INVITE` operator actions.

---

## 4. Key Protocol Rules

Before reading the code, keep these IRC rules in mind:

### Transmission Delimiters
Every IRC message sent from a client or a server must terminate with the character sequence **`\r\n`** (Carriage Return + Line Feed).
* When reading bytes from a client, we cannot assume that a single `recv` fetches exactly one complete command. The network might split a command into fragments, or group multiple commands into one block. We must append incoming data to a client-specific buffer and process messages only when a newline `\n` delimiter is parsed.

### Numeric Replies
IRC servers communicate state changes or errors to clients using **Numeric Replies**.
* These are 3-digit codes (e.g. `001` for Welcome, `433` for Nickname in use).
* Format: `:server_hostname <3-digit-code> <target_nickname> <parameters> :<message>`
* Defined in [Replies.hpp](file:///c:/42AD/staff-evaluation/irc/inc/Replies.hpp) and implemented in `sendNumeric()`.

---

## Next Steps

Let's study the core networking layer: **Sockets, select/poll, and I/O Multiplexing**.

👉 Proceed to [01_Sockets_and_IOMultiplexing.md](./01_Sockets_and_IOMultiplexing.md)
