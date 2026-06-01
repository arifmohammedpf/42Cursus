#include "Server.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

// Handles KICK for channel operators, removes the target from the channel
void Server::cmdKick(int fd, const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        sendNumeric(fd, ERR_NEEDMOREPARAMS, "KICK :Not enough parameters");
        return;
    }

    std::string channelName = args[0];
    std::string targetNick = args[1];
    std::string reason = (args.size() > 2) ? args[2] : "Kicked by operator";
    Client *sender = _clients[fd];

    if (_channels.find(channelName) == _channels.end())
    {
        sendNumeric(fd, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
        return;
    }

    Channel *channel = _channels[channelName];

    if (!channel->hasClient(sender))
    {
        sendNumeric(fd, ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
        return;
    }

    if (!channel->isOperator(sender))
    {
        sendNumeric(fd, ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");
        return;
    }

    if (sender->getNickname() == targetNick)
    {
        sendNumeric(fd, ERR_NOSUCHCHANNEL, channelName + " :You cannot kick yourself");
        return;
    }

    Client *targetClient = NULL;
    const std::set<Client *> &clients = channel->getClients();

    for (std::set<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if ((*it)->getNickname() == targetNick)
        {
            targetClient = *it;
            break;
        }
    }

    if (targetClient == NULL)
    {
        sendNumeric(fd, ERR_USERNOTINCHANNEL, targetNick + " " + channelName + " :They aren't on that channel");
        return;
    }

    // Standard IRC KICK format: :nick_operator!user_operator@ip KICK #channel targetNick :reason
    std::string kickMsg = ":" + sender->getNickname() + "!" + sender->getUsername() +
                          "@" + sender->getIpAddress() + " KICK " + channelName +
                          " " + targetNick + " :" + reason;

    channel->broadcast(kickMsg, NULL);

    channel->removeClient(targetClient);
    std::cout << targetNick << " was kicked from " << channelName << " by " << sender->getNickname() << std::endl;

    if (channel->getClients().empty())
    {
        std::cout << "Channel " << channelName << " is empty. Deleting it!" << std::endl;
        delete channel;
        _channels.erase(channelName);
    }
}

// Handles INVITE for channel operators, adds the target to the channel invite list.
void Server::cmdInvite(int fd, const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        sendNumeric(fd, ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");
        return;
    }

    std::string targetNick = args[0];
    std::string channelName = args[1];
    Client *sender = _clients[fd];

    if (_channels.find(channelName) == _channels.end())
    {
        sendNumeric(fd, ERR_NOSUCHCHANNEL, channelName + " :No such channel");
        return;
    }
    Channel *channel = _channels[channelName];

    if (!channel->hasClient(sender))
    {
        sendNumeric(fd, ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
        return;
    }

    if (!channel->isOperator(sender))
    {
        sendNumeric(fd, ERR_CHANOPRIVSNEEDED, channelName + " :You're not channel operator");
        return;
    }

    Client *targetClient = NULL;
    for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second->getNickname() == targetNick)
        {
            targetClient = it->second;
            break;
        }
    }

    if (targetClient == NULL)
    {
        sendNumeric(fd, ERR_NOSUCHNICK, targetNick + " :No such nick/channel");
        return;
    }

    if (channel->hasClient(targetClient))
    {
        sendNumeric(fd, ERR_USERONCHANNEL, targetNick + " " + channelName + " :is already on channel");
        return;
    }

    channel->inviteClient(targetClient);

    sendNumeric(fd, RPL_INVITING, targetNick + " " + channelName);

    // Standard IRC INVITE format: :nick_operator!user_operator@ip INVITE targetNick :#channel
    std::string inviteMsg = ":" + sender->getNickname() + "!" + sender->getUsername() +
                            "@" + sender->getIpAddress() + " INVITE " + targetNick + " :" + channelName;
    targetClient->sendMessage(inviteMsg);

    std::cout << targetNick << " was invited to " << channelName << " by " << sender->getNickname() << std::endl;
}
