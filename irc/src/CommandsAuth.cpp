#include "../inc/Server.hpp"
#include <iomanip>
#include "../inc/Replies.hpp"
#include "../inc/Channel.hpp"

static bool isValidNick(const std::string &nick)
{
	if (nick.empty() || nick.length() > 30)
		return false;

	char first = nick[0];
	bool firstOk = std::isalpha(first) || first == '[' || first == ']' ||
				   first == '\\' || first == '`' || first == '_' ||
				   first == '^' || first == '{' || first == '|' ||
				   first == '}';
	if (!firstOk)
		return false;

	for (size_t i = 1; i < nick.size(); ++i)
	{
		char c = nick[i];
		bool ok = std::isalnum(c) || c == '-' || c == '[' || c == ']' ||
				  c == '\\' || c == '`' || c == '_' || c == '^' ||
				  c == '{' || c == '|' || c == '}';
		if (!ok)
			return false;
	}
	return true;
}

void Server::cmdPass(int fd, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		sendNumeric(fd, ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
		return;
	}
	if (_clients[fd]->hasPassword())
	{
		sendNumeric(fd, ERR_ALREADYREGISTRED, ":You may not reregister");
		return;
	}
	if (args[0] != _password)
	{
		sendNumeric(fd, ERR_PASSWDMISMATCH, ":Password incorrect");
		return;
	}
	_clients[fd]->setHasPassword(true);
}

void Server::cmdNick(int fd, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		sendNumeric(fd, ERR_NONICKNAMEGIVEN, ":No nickname given");
		return;
	}

	std::string desiredNick = args[0];

	if (!isValidNick(desiredNick))
	{
		sendNumeric(fd, ERR_ERRONEUSNICKNAME, desiredNick + " :Erroneous nickname");
		return;
	}

	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->first != fd && it->second->getNickname() == desiredNick)
		{
			sendNumeric(fd, ERR_NICKNAMEINUSE, desiredNick + " :Nickname is already in use");
			return;
		}
	}

	std::string oldNick = _clients[fd]->getNickname();
	_clients[fd]->setNickname(desiredNick);
	std::cout << "FD " << fd << " nick: " << desiredNick << std::endl;

	if (_clients[fd]->isRegistered())
	{
		std::string nickMsg = ":" + oldNick + "!" + _clients[fd]->getUsername() +
							  "@" + _clients[fd]->getIpAddress() + " NICK :" + desiredNick;

		std::set<int> alreadyNotified;
		alreadyNotified.insert(fd);
		_clients[fd]->sendMessage(nickMsg);

		for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		{
			if (it->second->hasClient(_clients[fd]))
			{
				const std::set<Client *> &members = it->second->getClients();
				for (std::set<Client *>::iterator cit = members.begin(); cit != members.end(); ++cit)
				{
					if (alreadyNotified.find((*cit)->getFd()) == alreadyNotified.end())
					{
						(*cit)->sendMessage(nickMsg);
						alreadyNotified.insert((*cit)->getFd());
					}
				}
			}
		}
	}
	else
	{
		checkRegistration(fd);
	}
}

void Server::cmdUser(int fd, const std::vector<std::string> &args)
{
	if (_clients[fd]->isRegistered())
	{
		sendNumeric(fd, ERR_ALREADYREGISTRED, ":You may not reregister");
		return;
	}
	if (args.size() < 4)
	{
		sendNumeric(fd, ERR_NEEDMOREPARAMS, "USER :Not enough parameters");
		return;
	}
	if (!_clients[fd]->hasPassword())
	{
		sendNumeric(fd, ERR_PASSWDMISMATCH, ":Password required before USER");
		return;
	}

	std::string username = args[0];
	std::string realname = args[3];

	if (!realname.empty() && realname[0] == ':')
		realname = realname.substr(1);

	_clients[fd]->setUsername(username);
	std::cout << "FD " << fd << " username: " << username << std::endl;

	checkRegistration(fd);
}
