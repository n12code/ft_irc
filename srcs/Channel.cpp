/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:58:07 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/09 11:03:34 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(const std::string &name, const int creatorFd) : _name(name)
{
    this->addChanop(creatorFd);
}

Channel::~Channel() {}

bool Channel::hasMode(const char mode)
{
    if (this->_modes.find(mode) != this->_modes.end())
        return (true);
    return (false);
}

bool Channel::isInvited(const int fd)
{
    if (this->_invited.find(fd) != this->_invited.end())
        return (true);
    return (false);
}

bool Channel::isChanop(const int fd)
{
    if (this->_chanops.find(fd) != this->_chanops.end())
        return (true);
    return (false);
}

//utility

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
    this->removeUser(fd);
    this->_chanops.erase(fd);
}

void Channel::addUser(const int fd)
{
    this->_users.insert(fd);
}

void Channel::removeUser(const int fd)
{
    this->_users.erase(fd);
}

//getter

const std::string   Channel::getPassword() const
{
    return (this->_password);
}

const std::string   Channel::getName() const
{
    return (this->_name);
}

const std::set<int> Channel::getUsers() const
{
    return (this->_users);
}

std::size_t Channel::getMaxCap() const
{
    return (this->_maxCap);
}

//setter
void    Channel::setPassword(const std::string& password)
{
    this->_password = password;
}