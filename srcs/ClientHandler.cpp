/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/09/04 08:17:46 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClientHandler.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "command/CommandDispatcher.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>

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
        if (!msg.parseMessage(client->getBuffer()))
            return ;    
        if (!this->_dispatcher.dispatch(fd, msg))
        {
            std::string reason = "leaving";
            if (!msg.getParams().empty())
                reason = msg.getParams().at(0);
            this->broadcastQuit(fd, reason);
            this->onError(fd);
            msg.clearParsedData();
            return ;
        }

        const std::map<int, Client>&            allClients = this->_clients.getClients();
        std::map<int, Client>::const_iterator   it = allClients.begin();
        for (; it != allClients.end(); ++it)
        {
            if (!it->second.getMsgBuffer().empty())
                this->_loop.toggleWriteEvent(it->first, true);
        }
        msg.clearParsedData();
    }
}

void ClientHandler::onWritable(int& fd)
{
    Client&         client = this->_clients.getClientWithFd(fd);
    std::string&    buffer = client.getMsgBuffer();

    if (buffer.empty())
    {
        this->_loop.toggleWriteEvent(fd, false);
        return ;
    }

    ssize_t  bytesSent = send(fd, buffer.c_str(), buffer.length(), 0);
    if (bytesSent == -1)
    {
        std::cerr << "Warning: Client send error"<< std::endl;
        this->onError(fd); 
        return;
    }

    buffer.erase(0, static_cast<unsigned long> (bytesSent));

    if (buffer.empty())
        this->_loop.toggleWriteEvent(fd, false);
}
