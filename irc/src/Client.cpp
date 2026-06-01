#include "Client.hpp"

// ==========================================
// Flags initialized
// ==========================================
Client::Client(int fd, const std::string &ipAddress)
	: _fd(fd), _ipAddress(ipAddress), _buffer(""),
	  _nickname(""), _username(""),
	  _isRegistered(false), _hasPassword(false),
	  _hasUsername(false), _hasNickname(false) {}

Client::~Client() {}

// ==========================================
// GETTERS
// ==========================================
int Client::getFd() const
{
	return _fd;
}

std::string Client::getIpAddress() const
{
	return _ipAddress;
}

std::string Client::getBuffer() const
{
	return _buffer;
}

std::string Client::getNickname() const
{
	return _nickname;
}

std::string Client::getUsername() const
{
	return _username;
}

// ==========================================
// STATE CHECKERS
// ==========================================
bool Client::isRegistered() const
{
	return _isRegistered;
}

bool Client::hasPassword() const
{
	return _hasPassword;
}

bool Client::hasUsername() const
{
	return _hasUsername;
}

bool Client::hasNickname() const
{
	return _hasNickname;
}

// ==========================================
// SETTERS
// ==========================================
void Client::setNickname(const std::string &nickname)
{
	_nickname = nickname;
	_hasNickname = true;
}

void Client::setUsername(const std::string &username)
{
	_username = username;
	_hasUsername = true;
}

void Client::setRegistered(bool isRegistered)
{
	_isRegistered = isRegistered;
}

void Client::setHasPassword(bool hasPassword)
{
	_hasPassword = hasPassword;
}

void Client::setHasUsername(bool hasUsername)
{
	_hasUsername = hasUsername;
}

void Client::setHasNickname(bool hasNickname)
{
	_hasNickname = hasNickname;
}

// ==========================================
// BUFFER HELPERS
// ==========================================
void Client::appendToBuffer(const std::string &data)
{
	_buffer += data;
}

void Client::clearBuffer()
{
	_buffer.clear();
}

void Client::sendMessage(const std::string &message)
{
	// IRC protocol requires messages to end with \r\n
	std::string msg = message + "\r\n";
	send(_fd, msg.c_str(), msg.length(), 0);
}