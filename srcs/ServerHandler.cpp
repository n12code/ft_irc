/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/01 11:06:59 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ClientHandler.hpp"
#include "ClientManager.hpp"
#include "Client.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>

ServerHandler::ServerHandler(EventLoop &loop, ClientManager &clients) :
    EventHandler(loop, clients) {}

ServerHandler::~ServerHandler() {}

void    ServerHandler::onError(int fd)
{
    EventHandler::onError(fd);
    throw std::runtime_error("Error: server socket error");
}

void    ServerHandler::onReadable(const int fd)
{
    int connFd = accept4(fd, NULL, NULL, SOCK_NONBLOCK);
    if (connFd == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            std::cerr << "Warning: no connection pending: " << strerror(errno) << std::endl;
            return;
        }
        else if (errno == ENETDOWN || errno == EPROTO || errno == ENOPROTOOPT ||
            errno == EHOSTDOWN || errno == ENONET || errno == EHOSTUNREACH ||
            errno == EOPNOTSUPP || errno == ENETUNREACH)
        {
            std::cerr << "Warning: accept error: " << strerror(errno) << std::endl;
            return;
        }
        throw std::runtime_error(std::string("Error: accept failed: ") + strerror(errno));
    }
    this->_loop.registerHandler(connFd, new ClientHandler(this->_loop, this->_clients));
    this->_clients.addClient(Client(connFd));
}
