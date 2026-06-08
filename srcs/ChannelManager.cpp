/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:48:12 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/08 11:12:04 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelManager.hpp"
#include "Channel.hpp"
#include <string>
#include <map>
#include <stdexcept>


ChannelManager::ChannelManager():
    _channels(std::map<std::string, Channel>()) {}

ChannelManager::~ChannelManager() {}

Channel& ChannelManager::getChannelByName(const std::string &name)
{
    if (this->_channels.find(name) != this->_channels.end())
        return (this->_channels[name]);
    throw std::runtime_error("TEMP ERROR: Channel not found")//temp
}
