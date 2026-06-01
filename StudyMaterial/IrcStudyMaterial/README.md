# ft_irc Codebase Study Materials

This directory contains comprehensive study materials for the **ft_irc** project. These resources are designed to help you understand socket programming, event-driven I/O multiplexing (`poll`), data streams buffering, IRC commands parsing, and channel mode operations, enabling you to explain the codebase clearly during your defense.

---

## 📖 Chapter Index

| Chapter | File | Description | Key Concepts Covered |
|:---:|---|---|---|
| **0** | [00_Overview_and_Architecture.md](./00_Overview_and_Architecture.md) | High-level project architecture overview. | The IRC protocol, RFC 2812 compliance, application structure, and project directory maps. |
| **1** | [01_Sockets_and_IOMultiplexing.md](./01_Sockets_and_IOMultiplexing.md) | Network sockets configuration and multiplexing loop. | Socket setups, binding, backlog queues, non-blocking configurations (`O_NONBLOCK`), `poll()` event loop, and disconnections. |
| **2** | [02_Client_and_Channel_Classes.md](./02_Client_and_Channel_Classes.md) | User and Chat Room data model definitions. | `Client` structures, read buffers accumulation, socket write helpers, `Channel` set models, and broadcast loops. |
| **3** | [03_Authentication_Commands.md](./03_Authentication_Commands.md) | Commands parsing and connection handshakes. | Space-delimited tokenizers, trailing parameter isolation, routing, and registration commands (`PASS`, `NICK`, `USER`, `QUIT`). |
| **4** | [04_Channel_Commands_and_Modes.md](./04_Channel_Commands_and_Modes.md) | Channel creation, operations, and settings updates. | `JOIN` routines, empty channels cleanup (`PART`), topics management, and mode flag adjustments (`+i`, `+t`, `+k`, `+o`, `+l`). |
| **5** | [05_Chat_and_Operator_Privileges.md](./05_Chat_and_Operator_Privileges.md) | Messages routing and operator controls. | Chat distribution constraints (`PRIVMSG` vs. `NOTICE`), `KICK` logic, and client invitation lists (`INVITE`). |
| **6** | [06_Evaluation_Questions_and_Answers.md](./06_Evaluation_Questions_and_Answers.md) | Viva defense cheat sheet for evaluations. | TCP vs. UDP differences, non-blocking benefits, stream fragmentation checks, Windows carriage returns (`\r\n`), and resource leak preventions. |

---

## 🛠️ How to Use These Materials

1. **Start with Chapter 0:** Understand the high-level network topology and structural modules of the IRC server.
2. **Follow Code References:** Files and class methods are linked (e.g. `[Server.cpp]`) to let you jump straight to the source files on your system.
3. **Review the Q&A Cheat Sheet:** Use **Chapter 6** to prepare for evaluator questions, especially regarding socket configurations and buffer fragmentation.
