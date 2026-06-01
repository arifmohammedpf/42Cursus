#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(const std::string &name) : _name(name), _userLimit(0), _inviteOnly(false), _topicRestricted(false) {}

Channel::~Channel() {}

// ==========================================
// Getters
// ==========================================
const std::string &Channel::getName() const
{
	return _name;
}

const std::set<Client *> &Channel::getClients() const
{
	return _clients;
}

const std::string &Channel::getTopic() const
{
	return _topic;
}

const std::string &Channel::getKey() const
{
	return _password;
}

size_t Channel::getUserLimit() const
{
	return _userLimit;
}

// ==========================================
// Setters
// ==========================================
void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

void Channel::setInviteOnly(bool inviteOnly)
{
	_inviteOnly = inviteOnly;
}

void Channel::setTopicRestricted(bool restricted)
{
	_topicRestricted = restricted;
}

void Channel::setKey(const std::string &key)
{
	_password = key;
}

void Channel::setUserLimit(size_t limit)
{
	_userLimit = limit;
}

// ==========================================
// CHANNEL OPERATIONS
// ==========================================
void Channel::broadcast(const std::string &message, Client *exclude)
{
	for (std::set<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (exclude != NULL && *it == exclude)
			continue;
		(*it)->sendMessage(message);
	}
}

bool Channel::isTopicRestricted() const
{
	return _topicRestricted;
}

bool Channel::isInviteOnly() const
{
	return _inviteOnly;
}

bool Channel::isOperator(Client *client) const
{
	return _operators.find(client) != _operators.end();
}

bool Channel::isInvited(Client *client) const
{
	return _invitedClients.find(client) != _invitedClients.end();
}

// Invite is consumed once the client joins
void Channel::addClient(Client *client)
{
	_clients.insert(client);
	_invitedClients.erase(client);
}

void Channel::removeClient(Client *client)
{
	_clients.erase(client);
	_operators.erase(client);
	_invitedClients.erase(client);
}

void Channel::addOperator(Client *client)
{
	_operators.insert(client);
}

void Channel::removeOperator(Client *client)
{
	_operators.erase(client);
}

bool Channel::hasClient(Client *client) const
{
	return _clients.find(client) != _clients.end();
}

void Channel::inviteClient(Client *client)
{
	_invitedClients.insert(client);
}