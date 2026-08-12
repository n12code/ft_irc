/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 07:18:13 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/25 11:08:42 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Replies.hpp"
#include "ServerHandler.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <iostream>

Server::Server(const unsigned short port, const std::string pswd) :
    _socketFd(-1),
    _port(port),
    _pswd(pswd),
    _loop(),
    _clients(),
    _channels(),
    _dispatcher(CommandDispatcher(*this, this->_clients, this->_channels))
{
    setSocket();
    Replies::init();
}

Server::~Server() {}

void Server::setSocket()
{
    int opt = 1;
    
    this->_socketFd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (this->_socketFd == -1)
        throw std::runtime_error(std::string("Error: socket creation failed: ") + strerror(errno));
 
    if (setsockopt(this->_socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        throw std::runtime_error(std::string("Error: socket configuration failed: ") + strerror(errno));
    
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(this->_port);
    sin.sin_addr.s_addr = INADDR_ANY;
    if (::bind(this->_socketFd, reinterpret_cast<sockaddr*>(&sin), sizeof(sockaddr_in)) == -1)
        throw std::runtime_error(std::string("Error: socket binding failed: ") + strerror(errno));

    if (::listen(this->_socketFd, 128) == -1)
        throw std::runtime_error(std::string("Error: socket listening failed: ") + strerror(errno));
}

std::string Server::getPassword()
{
    return (this->_pswd);
}

const CommandDispatcher &Server::getDispatcher() const
{
    return (this->_dispatcher);
}

EventLoop &Server::getLoop()
{
    return (this->_loop);
}

void    Server::run()
{
    ServerHandler*   serverHandler = new ServerHandler(this->_loop, this->_clients, this->_channels, this->_dispatcher);
    
    this->_loop.initLoop();
    this->_loop.registerHandler(this->_socketFd, serverHandler);
    this->_loop.serverRoutine();
}

