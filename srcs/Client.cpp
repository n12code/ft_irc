/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:58:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/26 09:06:35 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Utils.hpp"
#include <string>

Client::Client() :
    _fd(-1),
    _auth(false),
    _registered(false),
    _buffer(""),
    _msgBuffer(""),
    _nick(""),
    _user(""),
    _realname(""),
    _host(""),
    _prefix ("") {}

Client::Client(int fd) :
    _fd(fd),
    _auth(false),
    _registered(false),
    _buffer(""),
    _msgBuffer(""),
    _nick(""),
    _user(""),
    _realname(""),
    _host(""),
    _prefix ("") {}

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

const std::string &Client::getMsgBuffer() const
{
    return (this->_msgBuffer);
}

std::string &Client::getMsgBuffer()
{
    return (this->_msgBuffer);
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
    std::string cpy = nick;
    Utils::toLowerIrc(cpy);
    this->_nick = cpy;
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

void    Client::sendMessage(const std::string& message)
{
    this->appendToBuffer(this->_msgBuffer, message);
}

void Client::appendToBuffer(std::string& buffer, const std::string &str)
{
    buffer += str;
}
