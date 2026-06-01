#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>

class Client;

class Channel {
    private:
        std::string _name;
        std::set<Client*> _clients;
        std::set<Client*> _operators;
        std::set<Client*> _invitedClients;

        std::string _topic;
        std::string _password;    // mode +k
        size_t      _userLimit;   // mode +l (0 means no limit)
        bool        _inviteOnly;  // mode +i
        bool        _topicRestricted; // mode +t

    public:
        Channel(const std::string &name);
        ~Channel();

        void addClient(Client* client);
        void removeClient(Client* client);
        void broadcast(const std::string &message, Client* exclude = NULL);

        const std::string &getName() const;
        const std::set<Client*> &getClients() const;
        const std::string &getTopic() const;
        bool isInviteOnly() const;
        const std::string& getKey() const;
        size_t getUserLimit() const;

        void addOperator(Client* client);
        bool isOperator(Client* client) const;
        bool hasClient(Client* client) const;
        void inviteClient(Client* client);
        bool isInvited(Client* client) const;
        void setTopic(const std::string& topic);
        bool isTopicRestricted() const;
        
        void setInviteOnly(bool inviteOnly);
        void setTopicRestricted(bool restricted);
        void setKey(const std::string& key);
        void setUserLimit(size_t limit);
        void removeOperator(Client* client);
};

#endif