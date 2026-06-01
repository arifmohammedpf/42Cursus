#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <sys/socket.h>


class Client {
    private:
        int _fd;
        std::string _ipAddress;
        std::string _buffer;

        std::string _nickname;
        std::string _username;

        bool _isRegistered;
        bool _hasPassword;
        bool _hasUsername;
        bool _hasNickname;

    public:
        Client(int fd, const std::string& ipAddress);
        ~Client();

        int getFd() const;
        std::string getIpAddress() const;
        std::string getBuffer() const;
        std::string getNickname() const;
        std::string getUsername() const;
        
        bool isRegistered() const;
        bool hasPassword() const;
        bool hasUsername() const;
        bool hasNickname() const;

        void setNickname(const std::string& nickname);
        void setUsername(const std::string& username);
        void setRegistered(bool isRegistered);
        void setHasPassword(bool hasPassword);
        void setHasUsername(bool hasUsername);
        void setHasNickname(bool hasNickname);

        void appendToBuffer(const std::string& data);
        void clearBuffer();

        void sendMessage(const std::string& message);
};

#endif