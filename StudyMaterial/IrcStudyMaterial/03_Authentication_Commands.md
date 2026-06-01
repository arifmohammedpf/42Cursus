# ft_irc — Authentication Commands & Parser

This document explains the parser that extracts commands from client buffers and the authentication sequence (`PASS`, `NICK`, `USER`, `QUIT`) defined in [Server.cpp](file:///c:/42AD/staff-evaluation/irc/src/Server.cpp), [Server_utils.cpp](file:///c:/42AD/staff-evaluation/irc/src/Server_utils.cpp), and [CommandsAuth.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsAuth.cpp).

---

## 1. Request Parsing (`Server::handleMessage`)

When a client buffer receives a complete command delimited by a newline, the string is routed to the parser.

```
Example raw input: "PRIVMSG #general :Hello World! How are you?"

  Tokens parsed:
    1. cmd   = "PRIVMSG"
    2. args  = ["#general"]
    3. Trailing argument (begins with ':'):
       Extracts remainder as: "Hello World! How are you?"
       args  = ["#general", "Hello World! How are you?"]
```

### [handleMessage](file:///c:/42AD/staff-evaluation/irc/src/Server.cpp#L131-L152)
* **What it is for:** Parses a raw command string into a command token and an arguments vector.
* **How it works:**
  1. Wraps the message in `std::istringstream` to read space-separated tokens.
  2. Extracts the first token as the command (`cmd`).
  3. Iterates through subsequent arguments:
     * If an argument begins with the character `':'`, it marks the start of a "trailing" argument that can contain spaces.
     * The parser reads the remaining string: `getline(iss, trailing)`.
     * Strips the leading `':'` and appends the combined trailing string to the arguments vector: `args.push_back(arg.substr(1) + trailing)`.
     * Breaks the loop immediately (the trailing argument is always the final parameter).
  4. Calls `parseCommand`.

---

## 2. Command Routing & Guard Rules

### [parseCommand](file:///c:/42AD/staff-evaluation/irc/src/Server.cpp#L154-L193)
* **What it is for:** Validates registration state and forwards command arguments to their respective handlers.
* **Why it is needed:** Secures the server by enforcing authentication constraints before allowing general commands.
* **How it works:**
  * If the client is **not registered**, it rejects all commands other than `PASS`, `NICK`, `USER`, `QUIT`, or `CAP` (which are needed to register). It returns `ERR_NOTREGISTERED` (`451`).
  * If valid, compares `cmd` against handlers (`JOIN`, `PRIVMSG`, `KICK`, etc.). Unknown commands return `ERR_UNKNOWNCOMMAND` (`421`).

---

## 3. The Authentication Sequence

To complete registration, a client must issue three commands in order: `PASS`, `NICK`, and `USER`.

```
                    Registration Workflow (checkRegistration)
                    
     PASS password  ──►  NICK nickname  ──►  USER username  ──►  Register Success
    (Sets hasPass)      (Sets hasNick)      (Sets hasUser)      (Sends RPL_WELCOME)
```

### [cmdPass](file:///c:/42AD/staff-evaluation/irc/src/CommandsAuth.cpp#L31-L49)
* **What it is for:** Sets and validates the server connection password.
* **Why it is needed:** Restricts access to authorized clients.
* **How it works:**
  * Checks if the client has already provided a password. If so, returns `ERR_ALREADYREGISTRED` (`462`).
  * Compares the input argument against the server's password. If it does not match, returns `ERR_PASSWDMISMATCH` (`464`).
  * If valid, sets `_hasPassword` to `true`.

### [cmdNick](file:///c:/42AD/staff-evaluation/irc/src/CommandsAuth.cpp#L51-L109)
* **What it is for:** Sets or changes the client's nickname.
* **How it works:**
  1. Asserts nickname argument is present. If missing, returns `ERR_NONICKNAMEGIVEN` (`431`).
  2. Runs `isValidNick` to check for forbidden characters:
     * Nickname must not be empty or exceed 30 characters.
     * The first character must be alphabetical or a permitted special symbol (e.g. `[`, `]`, `_`). It cannot be a digit or a hyphen.
     * Subsequent characters must be alphanumeric, hyphens, or permitted symbols.
     * If invalid, returns `ERR_ERRONEUSNICKNAME` (`432`).
  3. Iterates through `_clients` to ensure the desired nickname is not already in use. If a match is found, returns `ERR_NICKNAMEINUSE` (`433`).
  4. Updates the client's nickname and sets `_hasNickname = true`.
  5. **If the client is already registered:** Broadcasts the nickname change message (`:old_nick NICK :new_nick`) to the client and all members of channels they are in.
  6. **If not registered:** Calls `checkRegistration`.

### [cmdUser](file:///c:/42AD/staff-evaluation/irc/src/CommandsAuth.cpp#L111-L139)
* **What it is for:** Sets the client's username and realname.
* **How it works:**
  * Checks if the client is already registered. If so, returns `ERR_ALREADYREGISTRED`.
  * Verifies at least 4 arguments are present. If fewer, returns `ERR_NEEDMOREPARAMS` (`461`).
  * Asserts the client has already provided the password. If not, returns `ERR_PASSWDMISMATCH`.
  * Extracts username (`args[0]`) and realname (`args[3]`), stripping the leading `':'` from realname.
  * Updates the client's username and sets `_hasUsername = true`.
  * Calls `checkRegistration`.

---

## 4. Finalizing Registration (`Server::checkRegistration`)

### [checkRegistration](file:///c:/42AD/staff-evaluation/irc/src/Server_utils.cpp#L77-L93)
* **What it is for:** Completes client authentication.
* **Why it is needed:** Sends the required registration success packets.
* **How it works:**
  * Checks if `_hasPassword`, `_hasNickname`, and `_hasUsername` are all `true`.
  * If so, sets `_isRegistered = true`.
  * Transmits the standard welcome replies to the client socket:
    * `001` (`RPL_WELCOME`): Welcomes the user to the network.
    * `002`: Identifies the server version.
    * `003`: Identifies the creation date.
    * `004`: Lists server name, version, user modes, and channel modes.

---

## Next Steps

Now let's examine how channels are created, managed, and configured: **Channel Commands & Modes**.

👉 Proceed to [04_Channel_Commands_and_Modes.md](./04_Channel_Commands_and_Modes.md)
