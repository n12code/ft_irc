/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/23 09:46:22 by nbodin           ###   ########lyon.fr   */
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

void ClientHandler::onError(int& fd)
{
    Client&                     client = this->_clients.getClientWithFd(fd);
    std::vector<std::string>    chanOfUser = this->_channels.getChannelsOfUser(fd);

    if (client.isRegistered())
    {
        std::string quitMsg = ":" + client.getPrefix() + " QUIT :" ;
        
        for (size_t i = 0; i < chanOfUser.size(); ++i)
        {
            this->_channels.getChannelByName(chanOfUser[i]).removeUser(fd);
            if (this->_channels.getChannelByName(chanOfUser[i]).getUsers().size() == 0)
                this->_channels.removeChannel(chanOfUser[i]);
        }
    }
    this->_clients.removeClient(fd);
    EventHandler::onError(fd);
}

void    ClientHandler::broadcastQuit(int fd, const std::string& reason)
{
    Client&                     client = this->_clients.getClientWithFd(fd);
    std::vector<std::string>    chanOfUser = this->_channels.getChannelsOfUser(fd);

    if (client.isRegistered())
    {
        std::string quitMsg = ":" + client.getPrefix() + " QUIT :" + reason + "\r\n" ;
        
        for (size_t i = 0; i < chanOfUser.size(); ++i)
            this->_channels.getChannelByName(chanOfUser[i]).sendToChannel(quitMsg, this->_clients, fd);
    }
}

void ClientHandler::onReadable(int& fd)
{
    Message msg(this->_clients);
    if (!msg.readMessage(fd))
    {
        this->onError(fd);
        return ;
    }
    Client* client = NULL;
    for (;;)
    {
        client = &this->_clients.getClientWithFd(fd);
        std::cout << "BUFFER:\n" << client->getBuffer() << std::endl << std::endl;
        if (!msg.parseMessage(client->getBuffer()))
            return ;    
        if (!this->_dispatcher.dispatch(fd, msg))
        {
            std::string reason = msg.getParams()[0];
            this->broadcastQuit(fd, reason);
            this->onError(fd);
            msg.clearParsedData();
            return ;
        }
        msg.clearParsedData();
    }
}
