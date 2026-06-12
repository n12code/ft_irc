/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:48:12 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/12 07:38:09 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelManager.hpp"
#include "Channel.hpp"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>


ChannelManager::ChannelManager():
    _channels(std::map<std::string, Channel>()) {}

ChannelManager::~ChannelManager() {}

Channel& ChannelManager::getChannelByName(const std::string &name)
{
    return (this->_channels[name]);
}

bool ChannelManager::hasChannel(const std::string &name)
{
    if (this->_channels.find(name) != this->_channels.end())
        return (true);
    return (false);
}

Channel &ChannelManager::createChannel(const std::string &name, const int creatorFd)
{
    Channel channel(name, creatorFd);
    this->addChannel(channel);
    return (this->_channels[name]);
}

void ChannelManager::addChannel(Channel channel)
{
    this->_channels.insert(std::make_pair(channel.getName(), channel));
}

void ChannelManager::removeChannel(const std::string& name)
{
    this->_channels.erase(name);
}

std::vector<std::string> ChannelManager::getChannelsOfUser(const int clientFd)
{
    std::vector<std::string>            chanOfUser;
    std::map<std::string, Channel>::iterator  it = this->_channels.begin();
    for (; it != this->_channels.end(); ++it)
    {
        if (it->second.isUser(clientFd))
            chanOfUser.push_back(it->second.getName());
    }
    return (chanOfUser);
}