/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:56:08 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/12 09:01:23 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"
#include "Client.hpp"
#include <iterator>
#include <map>
#include <utility>
#include <stdexcept>

ClientManager::ClientManager() :
    _clients(std::map<int, Client>()) {}

ClientManager::~ClientManager() {}

Client& ClientManager::getClientWithFd(int fd)
{
    if (this->_clients.find(fd) != this->_clients.end())
        return (this->_clients[fd]);
    //client not found exception
    throw std::runtime_error("TEMP ERROR: Client not found"); //temp
}

Client& ClientManager::getClientWithNick(const std::string &nick)
{
    std::map<int, Client>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); ++it)
    {
        if (it->second.getNick() == nick)
            return (it->second);
    }
    throw std::runtime_error("TEMP ERROR: Client not found"); //temp
}

void    ClientManager::addClient(Client client)
{
    this->_clients.insert(std::make_pair(client.getFd(), client));
}

void    ClientManager::removeClient(int fd)
{
    this->_clients.erase(fd);
}

bool ClientManager::isNickInUse(const std::string& nick) const
{
    std::map<int, Client>::const_iterator it = _clients.begin();
    for (; it != this->_clients.end(); ++it)
    {
        if (it->second.getNick() == nick)
            return (true);
    }
    return (false);
}
