#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <poll.h>
#include <fcntl.h>       // For fcntl, O_NONBLOCK
#include <netinet/in.h>  // For sockaddr_in

class Client;
class Channel;
class Server {
    private:
        int _serverSocket;
        int _port;
        std::string _password;
        std::vector<pollfd> _pollfds;
        std::map<int, Client*> _clients;
        std::map<std::string, Channel*> _channels;
        
        void acceptConnection();
        void handleMessage(int fd, const std::string& message);
        void parseCommand(int fd, const std::string& cmd, const std::vector<std::string>& args);

        void cmdPass(int fd, const std::vector<std::string>& args);
        void cmdNick(int fd, const std::vector<std::string>& args);
        void cmdUser(int fd, const std::vector<std::string>& args);
        void cmdJoin(int fd, const std::vector<std::string>& args);
        void cmdPart(int fd, const std::vector<std::string>& args);
        void cmdPrivmsg(int fd, const std::vector<std::string>& args);
        void cmdNotice(int fd, const std::vector<std::string>& args);
        void cmdKick(int fd, const std::vector<std::string>& args);
        void cmdInvite(int fd, const std::vector<std::string>& args);
        void cmdTopic(int fd, const std::vector<std::string>& args);
        void cmdMode(int fd, const std::vector<std::string>& args);
        void cmdQuit(int fd, const std::vector<std::string>& args);
        void disconnectClient(int fd, const std::string& reason);
        Client* getClientByNick(const std::string& nick);
        void sendNumeric(int fd, int numeric, const std::string& message);
        void checkRegistration(int fd);
        
    public:
        Server(int port, const std::string &password);
        ~Server();
        void start();
};

#endif