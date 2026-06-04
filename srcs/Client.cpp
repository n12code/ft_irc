/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:58:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 11:16:55 by nbodin           ###   ########lyon.fr   */
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

std::string&    Client::getBuffer()
{
    return (this->_buffer);
}

std::string&    Client::getNick()
{
    return (this->_nick);
}

std::string&    Client::getUser()
{
    return (this->_user);
}