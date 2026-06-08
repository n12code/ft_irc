/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:58:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 08:07:12 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <string>

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

void Client::setAuth(bool auth)
{
    this->_auth = auth;
}

void Client::setRegistered(bool registered)
{
    this->_registered = registered;
}

void Client::setNick(const std::string& nick)
{
    this->_nick = nick;
}

void Client::setUser(const std::string& user)
{
    this->_user = user;
}
