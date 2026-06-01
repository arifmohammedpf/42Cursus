#include "Server.hpp"  
#include <iomanip> // For std::setfill and std::setw
#include "Replies.hpp"
#include "Channel.hpp"

void Server::sendNumeric(int fd, int numeric, const std::string& message) {
    Client* client = _clients[fd];
    if (!client) return;

    std::ostringstream oss;
    oss << std::setw(3) << std::setfill('0') << numeric;
    std::string numStr = oss.str();

    std::string nick = client->getNickname().empty() ? "*" : client->getNickname();

    std::string fullMsg = ":ft_irc " + numStr + " " + nick + " " + message;
    
    client->sendMessage(fullMsg);
}

Client* Server::getClientByNick(const std::string& nick) {
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nick) {
            return it->second;
        }
    }
    return NULL;
}

void Server::cmdQuit(int fd, const std::vector<std::string>& args) {
    std::string reason = "Client Quit";
    
    if (!args.empty()) {
        reason = args[0];
    }
    disconnectClient(fd, reason);
}

void Server::disconnectClient(int fd, const std::string& reason) {
    std::map<int, Client*>::iterator it = _clients.find(fd);
    if (it == _clients.end())
        return;

    Client* client = it->second;

    std::string quitMsg = ":" + client->getNickname() + "!" + client->getUsername() + 
                          "@" + client->getIpAddress() + " QUIT :" + reason;

    // Removing the user and broadcasting it to others
    for (std::map<std::string, Channel*>::iterator chanIt = _channels.begin(); chanIt != _channels.end(); /* increment inside */) {
        Channel* channel = chanIt->second;
        if (channel->hasClient(client)) {
            channel->broadcast(quitMsg, client);
            channel->removeClient(client);
            
            if (channel->getClients().empty()) {
                std::cout << "Channel " << chanIt->first << " is empty. Deleting it!" << std::endl;
                delete channel;
                _channels.erase(chanIt++);
                continue;
            }
        }
        ++chanIt;
    }
    for (std::vector<struct pollfd>::iterator pollIt = _pollfds.begin(); pollIt != _pollfds.end(); ++pollIt) {
        if (pollIt->fd == fd) {
            _pollfds.erase(pollIt);
            break;
        }
    }
    close(fd);
    delete client;
    _clients.erase(it);
    std::cout << "Client disconnected safely: " << fd << std::endl;
}

void Server::checkRegistration(int fd) {
    if (_clients[fd]->isRegistered())
        return;

    if (_clients[fd]->hasPassword() && _clients[fd]->hasNickname() && _clients[fd]->hasUsername()) {
        _clients[fd]->setRegistered(true);
        std::cout << "\n🌟 SUCCESS: Client FD " << fd << " (" << _clients[fd]->getNickname() << ") is now FULLY REGISTERED! 🌟\n" << std::endl;
        
        std::string nick = _clients[fd]->getNickname();
        std::string user = _clients[fd]->getUsername();
        std::string ip   = _clients[fd]->getIpAddress();

        _clients[fd]->sendMessage(":ft_irc 001 " + nick + " :Welcome to the ft_irc Network, " + nick + "!" + user + "@" + ip);
        _clients[fd]->sendMessage(":ft_irc 002 " + nick + " :Your host is ft_irc, running version 1.0");
        _clients[fd]->sendMessage(":ft_irc 003 " + nick + " :This server was created April 2026");
        _clients[fd]->sendMessage(":ft_irc 004 " + nick + " ft_irc 1.0 o itkol");
    }
}