/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 10:51:59 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClientHandler.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "CommandDispatcher.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <sys/epoll.h>

ClientHandler::ClientHandler(EventLoop &loop, ClientManager &clients, ChannelManager& channels, CommandDispatcher& dispatcher) :
    EventHandler(loop, clients, channels, dispatcher) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::onError(int fd)
{
    EventHandler::onError(fd);
    
    std::vector<std::string>    chanOfUser = this->_channels.getChannelsOfUser(fd);
    for (size_t i = 0; i < chanOfUser.size(); ++i)
        this->_channels.getChannelByName(chanOfUser[i]).removeUser(fd);
    this->_clients.removeClient(fd);
}

void ClientHandler::onReadable(const int fd)
{
    Message msg(this->_clients);
    if (!msg.readMessage(fd))
        this->onError(fd);
    Client* client = NULL;
    for (;;)
    {
        client = &this->_clients.getClientWithFd(fd);
        std::cout << "BUFFER:\n" << client->getBuffer() << std::endl << std::endl;
        if (!msg.parseMessage(client->getBuffer()))
            return ;    
        this->_dispatcher.dispatch(fd, msg);
        msg.clearParsedData();
    }
}
