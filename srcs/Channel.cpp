/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:58:07 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/23 07:32:42 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "ClientManager.hpp"
#include <iostream>

Channel::Channel():
    _name(""),
    _topic(""),
    _password(""),
    _maxCap(0) {}

Channel::Channel(const std::string &name, const int creatorFd) :
    _name(name),
    _topic(""),
    _password(""),
    _maxCap(0)
{
    this->addChanop(creatorFd);
}

Channel::~Channel() {}


bool Channel::hasMode(const char mode) const
{
    if (this->_modes.find(mode) != this->_modes.end())
        return (true);
    return (false);
}

bool Channel::isInvited(const int fd) const
{
    if (this->_invited.find(fd) != this->_invited.end())
        return (true);
    return (false);
}

bool Channel::isChanop(const int fd) const
{
    if (this->_chanops.find(fd) != this->_chanops.end())
        return (true);
    return (false);
}

bool Channel::isUser(const int fd) const
{
    if (this->_users.find(fd) != this->_users.end())
        return (true);
    return (false);
}

void Channel::addMode(const char mode)
{
    this->_modes.insert(mode);
}

void Channel::removeMode(const char mode)
{
    this->_modes.erase(mode);
}

void Channel::addInvited(const int fd)
{
    this->_invited.insert(fd);
}

void Channel::removeInvited(const int fd)
{
    this->_invited.erase(fd);
}

void Channel::addChanop(const int fd)
{
    this->addUser(fd);
    this->_chanops.insert(fd);
}

void Channel::removeChanop(const int fd)
{
    this->_chanops.erase(fd);
}

void Channel::addUser(const int fd)
{
    this->_users.insert(fd);
}

void Channel::removeUser(const int fd)
{
    this->_users.erase(fd);
    this->_chanops.erase(fd);
    this->_invited.erase(fd);
}

void Channel::sendToChannel(const std::string &message, ClientManager &clients, const int senderFd) const
{
    std::set<int>::const_iterator   it = this->_users.begin();
    Client*                         client = NULL;
    for (; it != this->_users.end(); ++it)
    {
        if (*it == senderFd)
            continue ;
        client = &clients.getClientWithFd(*it);
        client->sendMessage(message);
    }
}


const std::string   Channel::getPassword() const
{
    return (this->_password);
}

const std::string   Channel::getName() const
{
    return (this->_name);
}

const std::string Channel::getTopic() const
{
    return (this->_topic);
}

const std::set<int>& Channel::getUsers() const
{
    return (this->_users);
}

const std::set<int> &Channel::getInvited() const
{
    return (this->_invited);
}

std::size_t Channel::getMaxCap() const
{
    return (this->_maxCap);
}


void    Channel::setPassword(const std::string& password)
{
    this->_password = password;
}

void Channel::setTopic(const std::string &topic)
{
    this->_topic = topic;
}

void Channel::setMaxCap(const size_t& maxCap)
{
    this->_maxCap = maxCap;
}
