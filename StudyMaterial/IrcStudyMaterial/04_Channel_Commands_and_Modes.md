# ft_irc — Channel Commands & Modes

This document explains the commands used to create, join, leave, configure, and modify chat rooms. These functions are implemented in [CommandsChannel.cpp](file:///c:/42AD/staff-evaluation/irc/src/CommandsChannel.cpp).

---

## 1. Creating and Joining Channels (`JOIN`)

### [cmdJoin](file:///c:/42AD/staff-evaluation/irc/src/CommandsChannel.cpp#L6-L95)
* **What it is for:** Connects a client to a channel.
* **Why it is needed:** Primary channel navigation command.
* **How it works:**
  1. Asserts arguments exist. Checks channel name prefix: must start with `#` or `&`. If not, returns `ERR_NOSUCHCHANNEL` (`403`).
  2. **If the channel does not exist:**
     * Instantiates a new `Channel` object.
     * Adds the client to the channel's membership list.
     * Grants the client **operator** privileges: `addOperator()`.
     * Registers the channel in the server's `_channels` map.
  3. **If the channel already exists:**
     * If the client is already a member, returns immediately (noop).
     * **Invite-Only Guard (+i):** If the channel has the `inviteOnly` flag set, checks if the client is in `_invitedClients`. If not, rejects with `ERR_INVITEONLYCHAN` (`473`).
     * **Password Guard (+k):** If the channel has a password key, compares it with the client's second argument. If they do not match, rejects with `ERR_BADCHANNELKEY` (`475`).
     * **User Limit Guard (+l):** If the channel has a limit and is full, rejects with `ERR_CHANNELISFULL` (`471`).
     * Adds the client to the channel's membership list.
  4. Broadcasts a `JOIN` notification to all channel members.
  5. Transmits the channel's topic: `RPL_TOPIC` (`332`) or `RPL_NOTOPIC` (`331`).
  6. Transmits the channel member list: `RPL_NAMREPLY` (`353`) and `RPL_ENDOFNAMES` (`366`). Operators are prefixed with `@` in the list.

---

## 2. Leaving Channels (`PART`)

### [cmdPart](file:///c:/42AD/staff-evaluation/irc/src/CommandsChannel.cpp#L97-L137)
* **What it is for:** Disconnects a client from a channel.
* **How it works:**
  1. Checks if the channel exists. If not, returns `ERR_NOSUCHCHANNEL`.
  2. Checks if the client is currently in the channel. If not, returns `ERR_NOTONCHANNEL` (`442`).
  3. Broadcasts a `PART` message to the channel members.
  4. Removes the client from the channel's membership and operator lists.
  5. **Empty Channel Cleanup:** If the channel's membership list becomes empty, the server deletes the `Channel` object from memory and erases it from the `_channels` map to prevent memory leaks.

---

## 3. Topic Management (`TOPIC`)

### [cmdTopic](file:///c:/42AD/staff-evaluation/irc/src/CommandsChannel.cpp#L139-L190)
* **What it is for:** Reads or modifies a channel's topic description.
* **How it works:**
  * Checks if the channel exists and if the client is a member.
  * **Read Operation:** If the client only provided the channel name, it returns the current topic via `RPL_TOPIC` (`332`) or `RPL_NOTOPIC` (`331`).
  * **Write Operation:** If a new topic argument is provided:
    * If the channel has the topic-restricted flag active (`+t`), it verifies that the client is a channel operator. If not, rejects with `ERR_CHANOPRIVSNEEDED` (`482`).
    * Updates the topic string.
    * Broadcasts a `TOPIC` notification message to all channel members.

---

## 4. Channel Modes (`MODE`)

Channel modes alter how a channel behaves. The server supports five modes:

| Mode Flag | Mode Name | Description | Parameter Required |
| :---: | :--- | :--- | :--- |
| **`i`** | Invite-Only | Only invited users can join the channel. | No |
| **`t`** | Topic-Restricted | Only channel operators can change the topic. | No |
| **`k`** | Channel Key | Sets a password required to join. | Yes (to set/change) |
| **`o`** | Operator Privilege | Gives or removes operator privileges. | Yes (target nickname) |
| **`l`** | User Limit | Restricts maximum members count. | Yes (integer limit) |

### [cmdMode](file:///c:/42AD/staff-evaluation/irc/src/CommandsChannel.cpp#L192-L381)
* **What it is for:** Configures channel mode flags.
* **How it works:**
  * Checks if the channel exists.
  * **Query Operation:** If the client only provided the channel name, it returns the active modes and their parameters via `RPL_CHANNELMODEIS` (`324`).
  * **Update Operation:** If mode parameters are provided:
    1. Verifies the client is in the channel and is a channel operator.
    2. Parses the mode flag string (e.g. `"+ik"`, `"-t"`, `"+ol"`):
       * `+` sets the state to **adding** (`adding = true`).
       * `-` sets the state to **removing** (`adding = false`).
    3. Iterates through the characters:
       * **`i` / `t`**: Calls `setInviteOnly(adding)` or `setTopicRestricted(adding)`.
       * **`k`**:
         * If `adding`, reads the next argument as the key: `setKey(key)`.
         * If `removing`, clears the key: `setKey("")`.
       * **`l`**:
         * If `adding`, reads the next argument, converts it to an integer, and sets the limit: `setUserLimit(limit)`.
         * If `removing`, resets the limit to `0` (unlimited): `setUserLimit(0)`.
       * **`o`**:
         * Reads the next argument as the target nickname.
         * Looks up the target client. If the target is not in the channel, returns `ERR_USERNOTINCHANNEL` (`441`).
         * If `adding`, calls `addOperator(target)`.
         * If `removing`, calls `removeOperator(target)`.
    4. If any mode flags changed, broadcasts the mode update notification to all channel members.

---

## Next Steps

Now let's look at communication routing and admin commands: **Chat & Operator Privileges**.

👉 Proceed to [05_Chat_and_Operator_Privileges.md](./05_Chat_and_Operator_Privileges.md)
