#include "Server.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

extern bool g_running;
// Initializes the server by setting up a non-blocking listening socket on the specified port.
Server::Server(int port, const std::string &password) : _port(port), _password(password) {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0)
        throw std::runtime_error("Failed to create socket");
    int opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("Failed to set SO_REUSEADDR");
    if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Failed to set non-blocking mode");

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        throw std::runtime_error("Failed to bind socket");

    if (listen(_serverSocket, SOMAXCONN) < 0)
        throw std::runtime_error("Failed to listen on socket");

    struct pollfd pfd;
    pfd.fd = _serverSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollfds.push_back(pfd);
}

void Server::start() {
    std::cout << "Server started on port " << _port << "..." << std::endl;

    while (g_running) {
        int pollCount = poll(&_pollfds[0], _pollfds.size(), -1);
        // pollCount becomes -1 if interrupted by a signal (Ctrl+C).
        if (pollCount < 0 && g_running == false) {
            break;
        } else if (pollCount < 0) {
            throw std::runtime_error("Poll failed");
        }
        for (size_t i = 0; i < _pollfds.size(); i++) {
            if (_pollfds[i].revents & POLLIN) {
                if (_pollfds[i].fd == _serverSocket) {
                    acceptConnection();
                } 
                else {
                    int fd = _pollfds[i].fd;
                    char buffer[1024];
                    int bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);

                    if (bytes <= 0) {
                        disconnectClient(fd, "Client Disconnected");
                        i--;
                    } 
                    else {
                        buffer[bytes] = '\0'; 
                        _clients[fd]->appendToBuffer(buffer);
                        size_t pos;
                        while ((pos = _clients[fd]->getBuffer().find('\n')) != std::string::npos) {
                            std::string message = _clients[fd]->getBuffer().substr(0, pos);
                            if (!message.empty() && message[message.length() - 1] == '\r') {
                                message.erase(message.length() - 1);
                            }
                            
                            std::cout << "Complete command received from FD " << fd << ": [" << message << "]" << std::endl;
                            handleMessage(fd, message);
                            
                            if (_clients.find(fd) == _clients.end())
                                break;
                            std::string remaining = _clients[fd]->getBuffer().substr(pos + 1);
                            _clients[fd]->clearBuffer();
                            _clients[fd]->appendToBuffer(remaining);
                        }
                    }
                }
            }
        }
    }
}

void Server::acceptConnection() {
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int clientSocket = accept(_serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return;
    }
    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0) {
        std::cerr << "Failed to set non-blocking mode for client socket" << std::endl;
        close(clientSocket);
        return;
    }
    struct pollfd pfd;
    pfd.fd = clientSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollfds.push_back(pfd);
    
    std::string clientIP = inet_ntoa(clientAddr.sin_addr);
    std::cout << "Client connected (FD " << clientSocket << ", IP: " << clientIP << ")" << std::endl;
    _clients[clientSocket] = new Client(clientSocket, clientIP);
}

Server::~Server() {
    // Close the listening socket
    if (_serverSocket != -1) {
        close(_serverSocket);
    }
    std::map<int, Client*>::iterator it = _clients.begin();
    while (it != _clients.end()) {
        close(it->first);
        delete it->second;
        it++;
    }
    _clients.clear();
    std::map<std::string, Channel*>::iterator it2 = _channels.begin();
    while (it2 != _channels.end()) {
        delete it2->second;
        it2++;
    }
    _channels.clear();
}

void Server::handleMessage(int fd, const std::string& message) {
    if (message.empty())
        return;

    std::istringstream iss(message);
    std::string cmd;
    iss >> cmd;

    std::vector<std::string> args;
    std::string arg;
    
    while (iss >> arg) {
        if (arg[0] == ':') {
            std::string trailing;
            std::getline(iss, trailing);
            args.push_back(arg.substr(1) + trailing);
            break;
        }
        args.push_back(arg);
    }
    parseCommand(fd, cmd, args);
}

void Server::parseCommand(int fd, const std::string& cmd, const std::vector<std::string>& args) {
    if (!_clients[fd]->isRegistered() && cmd != "PASS" && cmd != "NICK" && cmd != "USER" && cmd != "QUIT" && cmd != "CAP") {
        sendNumeric(fd, ERR_NOTREGISTERED, ":You have not registered");
        return;
    }
    if (cmd == "PASS") {
        cmdPass(fd, args);
    } else if (cmd == "NICK") {
        cmdNick(fd, args);
    } else if (cmd == "USER") {
        cmdUser(fd, args);
    } else if (cmd == "QUIT") {
        cmdQuit(fd, args);
    } else if (cmd == "JOIN") {
        cmdJoin(fd, args);
    } else if (cmd == "PART") {
        cmdPart(fd, args);
    } else if (cmd == "PING") {
        if (!args.empty()) {
            _clients[fd]->sendMessage(":ft_irc PONG ft_irc :" + args[0]);
            std::cout << "FD " << fd << " sent PING, replied with PONG." << std::endl;
        }
    } else if (cmd == "CAP") {
        // Silently ignore capability requests (modern IRC clients send this on connect)
    } else if (cmd == "KICK") {
        cmdKick(fd, args);
    } else if (cmd == "PRIVMSG") {
        cmdPrivmsg(fd, args);
    } else if (cmd == "NOTICE") {
        cmdNotice(fd, args);
    } else if (cmd == "INVITE") {
        cmdInvite(fd, args);
    } else if (cmd == "TOPIC") {
        cmdTopic(fd, args);
    } else if (cmd == "MODE") {
        cmdMode(fd, args);
    } else {
        sendNumeric(fd, ERR_UNKNOWNCOMMAND, cmd + " :Unknown command");
    }
}
