#include "Server.hpp"
#include <iostream>
#include <cstdlib>
#include <csignal>

bool g_running = true;

void signalHandler(int signum) {
    (void)signum;
    std::cout << "\n[*] Shutting down server..." << std::endl;
    g_running = false;
}

void printUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <port> <password>" << std::endl;
    std::cerr << "  port     : Port number to listen on (1024-65535)" << std::endl;
    std::cerr << "  password : Connection password for clients" << std::endl;
}

bool isValidPort(const char* portStr) {
    for (int i = 0; portStr[i]; i++) {
        if (!std::isdigit(portStr[i])) {
            return false;
        }
    }
    int port = std::atoi(portStr);
    return port >= 1024 && port <= 65535;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }

    if (!isValidPort(argv[1])) {
        std::cerr << "Error: Invalid port. Must be between 1024 and 65535." << std::endl;
        return 1;
    }

    if (std::string(argv[2]).empty()) {
        std::cerr << "Error: Password cannot be empty." << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    std::string password = argv[2];

    // Set up signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    try {
        Server server(port, password);
        
        std::cout << "========================================" << std::endl;
        std::cout << "         ft_irc Server v1.0             " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Port: " << port << std::endl;
        std::cout << "Password: " << std::string(password.length(), '*') << std::endl;
        std::cout << "Press Ctrl+C to shutdown" << std::endl;
        std::cout << "========================================" << std::endl;

        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
