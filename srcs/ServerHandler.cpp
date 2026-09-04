/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/09/04 07:41:37 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ClientHandler.hpp"
#include "ClientManager.hpp"
#include "ChannelManager.hpp"
#include "command/CommandDispatcher.hpp"
#include "Client.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

ServerHandler::ServerHandler(EventLoop &loop, ClientManager &clients, ChannelManager &channels, CommandDispatcher& dispatcher) :
    EventHandler(loop, clients, channels, dispatcher) {}

ServerHandler::~ServerHandler() {}

void    ServerHandler::onError(int& fd)
{
    EventHandler::onError(fd);
    throw std::runtime_error("Error: server socket error");
}

void    ServerHandler::onReadable(int& fd)
{
    sockaddr_in client_addr;
    socklen_t   len = sizeof(client_addr);
    int connFd = accept4(fd, reinterpret_cast<sockaddr*>(&client_addr), &len, SOCK_NONBLOCK);
    if (connFd == -1)
    {
        std::cerr << "Warning: accept failed" << std::endl;
        return ;
    }
    this->_loop.registerHandler(connFd, new ClientHandler(this->_loop, this->_clients, this->_channels, this->_dispatcher));
    this->_clients.addClient(Client(connFd));
    this->_clients.getClientWithFd(connFd).setHost(inet_ntoa(client_addr.sin_addr));
}
    