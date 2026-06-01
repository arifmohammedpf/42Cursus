#include "Server.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

// Handles PRIVMSG delivery to a channel or a single user.
// Channel messages are broadcast to members except the sender.
void Server::cmdPrivmsg(int fd, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		sendNumeric(fd, ERR_NORECIPIENT, ":No recipient given (PRIVMSG)");
		return;
	}

	if (args.size() < 2 || args[1].empty())
	{
		sendNumeric(fd, ERR_NOTEXTTOSEND, ":No text to send");
		return;
	}

	std::string target = args[0];
	std::string message = args[1];
	Client *client = _clients[fd];

	// Standard IRC message format: :nick!user@host PRIVMSG target :message
	std::string fullMsg = ":" + client->getNickname() + "!" + client->getUsername() +
												"@" + client->getIpAddress() + " PRIVMSG " + target + " :" + message;

	if (target[0] == '#' || target[0] == '&')
	{
		if (_channels.find(target) == _channels.end())
		{
			sendNumeric(fd, ERR_NOSUCHNICK, target + " :No such nick/channel");
			return;
		}

		Channel *channel = _channels[target];

		if (!channel->hasClient(client))
		{
			sendNumeric(fd, ERR_CANNOTSENDTOCHAN, target + " :Cannot send to channel");
			return;
		}
		channel->broadcast(fullMsg, client);
	}
	else
	{
		bool userFound = false;

		for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if (it->second->getNickname() == target)
			{
				it->second->sendMessage(fullMsg);
				userFound = true;
				break;
			}
		}

		if (!userFound)
		{
			sendNumeric(fd, ERR_NOSUCHNICK, target + " :No such nick/channel");
		}
	}
}

// Handles NOTICE delivery to a channel or a single user.
// Channel notices are broadcast to members except the sender.
void Server::cmdNotice(int fd, const std::vector<std::string> &args)
{
	if (args.size() < 2)
	{
		return;
	}

	std::string target = args[0];
	std::string message = args[1];
	Client *client = _clients[fd];

	// Standard IRC message format: :nick!user@host NOTICE target :message
	std::string fullMsg = ":" + client->getNickname() + "!" + client->getUsername() +
												"@" + client->getIpAddress() + " NOTICE " + target + " :" + message;

	if (target[0] == '#' || target[0] == '&')
	{
		if (_channels.find(target) == _channels.end())
			return;

		Channel *channel = _channels[target];
		if (!channel->hasClient(client))
			return;

		channel->broadcast(fullMsg, client);
	}
	else
	{
		for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if (it->second->getNickname() == target)
			{
				it->second->sendMessage(fullMsg);
				break;
			}
		}
	}
}
