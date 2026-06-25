/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:56:08 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/25 10:59:25 by nbodin           ###   ########lyon.fr   */
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
    return this->_clients.at(fd);
}

Client& ClientManager::getClientWithNick(const std::string &nick)
{
    std::map<int, Client>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); ++it)
    {
        if (it->second.getNick() == nick)
            return (it->second);
    }
    return (this->_clients.begin()->second);
}

const std::map<int, Client>& ClientManager::getClients() const
{
    return (this->_clients);
}

void    ClientManager::addClient(Client client)
{
    this->_clients.insert(std::make_pair(client.getFd(), client));
}

void    ClientManager::removeClient(int fd)
{
    this->_clients.erase(fd);
}

bool ClientManager::hasClient(const std::string& nick) const
{
    std::map<int, Client>::const_iterator it = _clients.begin();
    for (; it != this->_clients.end(); ++it)
    {
        if (it->second.getNick() == nick)
            return (true);
    }
    return (false);
}
