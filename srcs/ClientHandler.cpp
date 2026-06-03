/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/03 12:05:21 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClientHandler.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <sys/epoll.h>

ClientHandler::ClientHandler(EventLoop &loop, ClientManager &clients) :
    EventHandler(loop, clients) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::onError(int fd)
{
    EventHandler::onError(fd);
    //remove from channels
    this->_clients.removeClient(fd);
}

void ClientHandler::onReadable(const int fd)
{
    Message msg(this->_clients);
    if (!msg.readMessage(fd))
        this->onError(fd);
    //NEED TO RETHINK MESSAGE READING AND COMMAND DISPATCHING ARHCITECTURE
    for (;;)
    {
        Client& client = this->_clients.getClientWithFd(fd);
        // std::cout << "buffer:\n" << client.getBuffer() << std::endl;
        if (!msg.parseMessage(client.getBuffer()))
            return ;
        //pass to command dispatcher
        msg.clearParsedData();
    }
}
