/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:58:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/23 07:27:34 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <string>
#include <sys/socket.h>

Client::Client() :
    _fd(-1),
    _buffer("") {}

Client::Client(int fd) :
    _fd(fd),
    _buffer("") {}

Client::Client(const Client &copy) :
    _fd(copy._fd),
    _buffer(copy._buffer) {}

Client::~Client() {}

int&    Client::getFd()
{
    return (this->_fd);
}

bool    Client::isRegistered()
{
    return (this->_registered);
}

bool    Client::isAuth()
{
    return (this->_auth);
}

const std::string&    Client::getBuffer() const
{
    return (this->_buffer);
}

std::string&    Client::getBuffer()
{
    return (this->_buffer);
}

const std::string&    Client::getNick() const
{
    return (this->_nick);
}

const std::string&    Client::getUser() const
{
    return (this->_user);
}

const std::string&    Client::getHost() const
{
    return (this->_host);
}

const std::string &Client::getPrefix() const
{
    return (this->_prefix);
}

const std::string &Client::getRealName() const
{
    return (this->_realname);
}

void    Client::setAuth(bool auth)
{
    this->_auth = auth;
}

void    Client::setRegistered(bool registered)
{
    this->_registered = registered;
}

void    Client::setNick(const std::string& nick)
{
    this->_nick = nick;
}

void    Client::setUser(const std::string& user)
{
    this->_user = user;
}

void Client::setHost(const std::string &host)
{
    this->_host = host;
}

void Client::setPrefix(const std::string &prefix)
{
    this->_prefix = prefix;
}

void Client::setRealName(const std::string &realname)
{
    this->_realname = realname;
}

void    Client::sendMessage(const std::string& message) const
{
    if (message.length() < 2 || this->_fd == -1)
        return;
        
    ssize_t sent = 0;
    for (size_t total = 0; total < message.length(); total += sent)
    {
        sent = send(this->_fd, message.c_str() + total, message.length() - total, 0);
        if (sent <= 0)
            break; //error or socket closed, escape cleanly
    }
}

void Client::appendToBuffer(const std::string &str)
{
    this->_buffer += str;
}
