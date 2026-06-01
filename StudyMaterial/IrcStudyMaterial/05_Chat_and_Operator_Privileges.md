# ft_irc — Chat Routing & Operator Privileges

This document explains the message delivery system (`PRIVMSG`, `NOTICE`) and administrative channel commands (`KICK`, `INVITE`) defined in [CommandsChat.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsChat.cpp) and [CommandsOper.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsOper.cpp).

---

## 1. Message Delivery Systems (`PRIVMSG` vs. `NOTICE`)

`PRIVMSG` and `NOTICE` are the primary commands used to send messages. They share similar routing logic but have one critical protocol difference: **`NOTICE` must never trigger error replies**.

```
                           PRIVMSG Message Routing
                                      │
              Is Target a Channel (starts with # or &)?
                 ├──► Yes:
                 │    Verify channel exists.
                 │    Verify sender is a member.
                 │    Broadcast message to all members except sender.
                 │
                 └──► No (Target is a nickname):
                      Search active client list for nickname.
                      ├──► Found: Send message to target socket.
                      └──► Not Found: Send ERR_NOSUCHNICK (401).
```

### [cmdPrivmsg](file:///c:/42AD/staff-evaluation/irc/src/CommandsChat.cpp#L7-L65)
* **What it is for:** Sends private messages to users or channels.
* **How it works:**
  1. Asserts target recipient is present. If missing, returns `ERR_NORECIPIENT` (`411`).
  2. Asserts text is present. If missing, returns `ERR_NOTEXTTOSEND` (`412`).
  3. Formats the standard message header:
     `:sender_nickname!sender_username@sender_ip PRIVMSG <target> :<message>`
  4. **Target is a Channel (starts with `#` or `&`):**
     * Checks if the channel exists. If not, returns `ERR_NOSUCHNICK` (`401`).
     * Checks if the sender is currently inside the channel. If not, returns `ERR_CANNOTSENDTOCHAN` (`404`) (preventing external spamming).
     * Calls `channel->broadcast` to send the message to all members except the sender.
  5. **Target is a User:**
     * Searches the `_clients` map for the client with the matching nickname.
     * If found, calls `sendMessage` to transmit the message to that client's socket.
     * If not found, returns `ERR_NOSUCHNICK` (`401`).

### [cmdNotice](file:///c:/42AD/staff-evaluation/irc/src/CommandsChat.cpp#L69-L106)
* **What it is for:** Sends notifications to users or channels.
* **Why it is needed:** The IRC protocol forbids sending automatic replies to a `NOTICE` command to prevent infinite loops between automated programs or bots (e.g. Bot A sends error reply to Bot B, which replies with an error, looping infinitely).
* **How it works:** Implements the same routing logic as `PRIVMSG`, but **completely omits error replies**. If a channel or user does not exist, the command is silently ignored.

---

## 2. Operator Privileges (`KICK` & `INVITE`)

These commands allow channel operators (ops) to manage channel members.

### [cmdKick](file:///c:/42AD/staff-evaluation/irc/src/CommandsOper.cpp#L6-L79)
* **What it is for:** Removes a user from a channel.
* **How it works:**
  1. Asserts channel and target parameters are present. If missing, returns `ERR_NEEDMOREPARAMS` (`461`).
  2. Verifies the channel exists. If not, returns `ERR_NOSUCHCHANNEL` (`403`).
  3. Verifies the sender is in the channel. If not, returns `ERR_NOTONCHANNEL` (`442`).
  4. **Operator Check:** Verifies the sender is a channel operator. If not, rejects with `ERR_CHANOPRIVSNEEDED` (`482`).
  5. Verifies the target client is inside the channel. If not, returns `ERR_USERNOTINCHANNEL` (`441`).
  6. Formats the standard kick message:
     `:operator!user@host KICK <channel> <target> :<reason>`
  7. Broadcasts the kick message to all channel members.
  8. Removes the target client from the channel's membership, operator, and invite lists.
  9. **Empty Channel Cleanup:** If the channel becomes empty, deletes it from memory.

### [cmdInvite](file:///c:/42AD/staff-evaluation/irc/src/CommandsOper.cpp#L82-L145)
* **What it is for:** Invites a client to a channel.
* **How it works:**
  1. Asserts target nickname and channel parameters are present.
  2. Verifies the channel exists and the sender is a member.
  3. **Operator Check:** Verifies the sender is a channel operator. If not, rejects with `ERR_CHANOPRIVSNEEDED` (`482`).
  4. Searches the `_clients` map for the target nickname. If not found, returns `ERR_NOSUCHNICK` (`401`).
  5. Verifies the target client is not already inside the channel. If they are, returns `ERR_USERONCHANNEL` (`443`).
  6. Adds the target client to the channel's `_invitedClients` set.
  7. Transmits `RPL_INVITING` (`341`) to the operator to confirm the invite.
  8. Formats the invite notification:
     `:operator!user@host INVITE <target> :<channel>`
     Sends it directly to the target client's socket, alerting them of the invitation.
