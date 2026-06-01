#include "Server.hpp"
#include "Replies.hpp"
#include "Channel.hpp"
#include <cstdlib>

void Server::cmdJoin(int fd, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		sendNumeric(fd, ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters");
		return;
	}

	std::string channelName = args[0];
	if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
	{
		sendNumeric(fd, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
		return;
	}

	Client *client = _clients[fd];

	// checking channel is there or not ? creating it
	if (_channels.find(channelName) == _channels.end())
	{
		_channels[channelName] = new Channel(channelName);
		_channels[channelName]->addClient(client);
		_channels[channelName]->addOperator(client);
		std::cout << client->getNickname() << " created channel " << channelName << std::endl;
	}
	else
	{
		Channel *channel = _channels[channelName];

		if (channel->hasClient(client))
		{
			return;
		}

		// Invite-Only (+i)
		if (channel->isInviteOnly() && !channel->isInvited(client))
		{
			sendNumeric(fd, ERR_INVITEONLYCHAN, channelName + " :Cannot join channel (+i)");
			return;
		}

		// Password/Key (+k)
		if (!channel->getKey().empty())
		{
			std::string providedKey = (args.size() > 1) ? args[1] : "";
			if (providedKey != channel->getKey())
			{
				sendNumeric(fd, ERR_BADCHANNELKEY, channelName + " :Cannot join channel (+k)");
				return;
			}
		}

		// User Limit (+l)
		if (channel->getUserLimit() > 0 && channel->getClients().size() >= channel->getUserLimit())
		{
			sendNumeric(fd, ERR_CHANNELISFULL, channelName + " :Cannot join channel (+l)");
			return;
		}

		channel->addClient(client);
		std::cout << client->getNickname() << " joined channel " << channelName << std::endl;
	}

	// Format: :nickname!username@ip JOIN :#channelname
	std::string joinMsg = ":" + client->getNickname() + "!" + client->getUsername() +
						  "@" + client->getIpAddress() + " JOIN :" + channelName;
	_channels[channelName]->broadcast(joinMsg, NULL);

	if (_channels[channelName]->getTopic().empty())
		sendNumeric(fd, RPL_NOTOPIC, channelName + " :No topic is set");
	else
		sendNumeric(fd, RPL_TOPIC, channelName + " :" + _channels[channelName]->getTopic());

	Channel *targetChannel = _channels[channelName];
	std::string nickList = "";
	const std::set<Client *> &clientsInRoom = targetChannel->getClients();

	for (std::set<Client *>::iterator it = clientsInRoom.begin(); it != clientsInRoom.end(); ++it)
	{
		// for operator
		if (targetChannel->isOperator(*it))
		{
			nickList += "@";
		}
		nickList += (*it)->getNickname() + " ";
	}

	sendNumeric(fd, 353, "= " + channelName + " :" + nickList);
	sendNumeric(fd, 366, channelName + " :End of /NAMES list.");
}

void Server::cmdPart(int fd, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		sendNumeric(fd, ERR_NEEDMOREPARAMS, "PART :Not enough parameters");
		return;
	}

	std::string channelName = args[0];
	std::string reason = (args.size() > 1) ? args[1] : "Leaving";
	Client *client = _clients[fd];

	if (_channels.find(channelName) == _channels.end())
	{
		sendNumeric(fd, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
		return;
	}

	Channel *channel = _channels[channelName];

	if (!channel->hasClient(client))
	{
		sendNumeric(fd, ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
		return;
	}

	std::string partMsg = ":" + client->getNickname() + "!" + client->getUsername() +
						  "@" + client->getIpAddress() + " PART " + channelName + " :" + reason;

	channel->broadcast(partMsg, NULL);

	channel->removeClient(client);
	std::cout << client->getNickname() << " left channel " << channelName << std::endl;

	if (channel->getClients().empty())
	{
		std::cout << "Channel " << channelName << " is empty. Deleting it!" << std::endl;
		delete channel;
		_channels.erase(channelName);
	}
}

void Server::cmdTopic(int fd, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		sendNumeric(fd, ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters");
		return;
	}

	std::string channelName = args[0];
	Client *client = _clients[fd];

	if (_channels.find(channelName) == _channels.end())
	{
		sendNumeric(fd, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
		return;
	}
	Channel *channel = _channels[channelName];

	if (!channel->hasClient(client))
	{
		sendNumeric(fd, ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
		return;
	}

	if (args.size() == 1)
	{
		if (channel->getTopic().empty())
		{
			sendNumeric(fd, RPL_NOTOPIC, channelName + " :No topic is set");
		}
		else
		{
			sendNumeric(fd, RPL_TOPIC, channelName + " :" + channel->getTopic());
		}
		return;
	}

	std::string newTopic = args[1];

	if (channel->isTopicRestricted() && !channel->isOperator(client))
	{
		sendNumeric(fd, ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");
		return;
	}

	channel->setTopic(newTopic);

	std::string topicMsg = ":" + client->getNickname() + "!" + client->getUsername() +
						   "@" + client->getIpAddress() + " TOPIC " + channelName + " :" + newTopic;

	channel->broadcast(topicMsg, NULL);
}

void Server::cmdMode(int fd, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		sendNumeric(fd, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
		return;
	}

	std::string channelName = args[0];
	Client *client = _clients[fd];

	if (!channelName.empty() && channelName[0] != '#' && channelName[0] != '&')
	{
		return;
	}

	if (_channels.find(channelName) == _channels.end())
	{
		sendNumeric(fd, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
		return;
	}
	Channel *channel = _channels[channelName];

	if (args.size() == 1)
	{
		std::string modes = "+";
		std::string modeParams;
		if (channel->isInviteOnly())
			modes += "i";
		if (channel->isTopicRestricted())
			modes += "t";
		if (!channel->getKey().empty())
		{
			modes += "k";
			modeParams += " " + channel->getKey();
		}
		if (channel->getUserLimit() > 0)
		{
			modes += "l";
			std::ostringstream oss;
			oss << channel->getUserLimit();
			modeParams += " " + oss.str();
		}
		if (modes == "+")
			modes = "+";
		sendNumeric(fd, RPL_CHANNELMODEIS, channelName + " " + modes + modeParams);
		return;
	}

	std::string modeString = args[1];

	if (!channel->hasClient(client))
	{
		sendNumeric(fd, ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
		return;
	}

	if (!channel->isOperator(client))
	{
		sendNumeric(fd, ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");
		return;
	}

	bool adding = true;
	size_t paramIndex = 2;
	bool modeChanged = false;
	for (size_t i = 0; i < modeString.length(); ++i)
	{
		char c = modeString[i];

		if (c == '+')
		{
			adding = true;
		}
		else if (c == '-')
		{
			adding = false;
		}
		else
		{
			switch (c)
			{
			case 'i':
				if (adding)
					channel->setInviteOnly(true);
				else
					channel->setInviteOnly(false);
				modeChanged = true;
				break;

			case 't':
				if (adding)
					channel->setTopicRestricted(true);
				else
					channel->setTopicRestricted(false);
				modeChanged = true;
				break;

			case 'k':
				if (adding)
				{
					if (paramIndex < args.size())
					{
						channel->setKey(args[paramIndex]);
						paramIndex++;
						modeChanged = true;
					}
					else
					{
						sendNumeric(fd, ERR_NEEDMOREPARAMS, channelName + " +k :Not enough parameters");
					}
				}
				else
				{
					channel->setKey("");
					modeChanged = true;
				}
				break;

			case 'o':
				// Both adding (+o) and removing (-o) require a target nickname!
				if (paramIndex < args.size())
				{
					std::string targetNick = args[paramIndex];
					paramIndex++;
					Client *targetClient = getClientByNick(targetNick);

					if (!targetClient || !channel->hasClient(targetClient))
					{
						sendNumeric(fd, ERR_USERNOTINCHANNEL, targetNick + " " + channelName + " :They aren't on that channel");
					}
					else
					{
						if (adding)
							channel->addOperator(targetClient);
						else
							channel->removeOperator(targetClient);
						modeChanged = true;
					}
				}
				else
				{
					sendNumeric(fd, ERR_NEEDMOREPARAMS, channelName + " +o :Not enough parameters");
				}
				break;

			case 'l':
				if (adding)
				{
					if (paramIndex < args.size())
					{
						int limit = std::atoi(args[paramIndex].c_str());
						if (limit > 0)
						{
							channel->setUserLimit(limit);
							modeChanged = true;
						}
						paramIndex++;
					}
					else
					{
						sendNumeric(fd, ERR_NEEDMOREPARAMS, channelName + " +l :Not enough parameters");
					}
				}
				else
				{
					channel->setUserLimit(0);
					modeChanged = true;
				}
				break;

			default:
				std::string unknownMode(1, c);
				sendNumeric(fd, ERR_UNKNOWNMODE, unknownMode + " :is unknown mode char to me for " + channelName);
				break;
			}
		}
	}

	if (modeChanged)
	{
		std::string modeBroadcast = ":" + client->getNickname() + "!" + client->getUsername() +
									"@" + client->getIpAddress() + " MODE " + channelName + " " + modeString;
		for (size_t i = 2; i < args.size(); ++i)
		{
			modeBroadcast += " " + args[i];
		}
		channel->broadcast(modeBroadcast, NULL);
	}
}