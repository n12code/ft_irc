/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:58:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/01 10:40:24 by nbodin           ###   ########lyon.fr   */
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

std::string&    Client::getBuffer()
{
    return (this->_buffer);
}

int&    Client::getFd()
{
    return (this->_fd);
}