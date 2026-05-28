/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 07:18:13 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 07:36:38 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cerrno>

// socket()
// setsockopt()
// bind()
// listen()
// epoll()
//     check for "errors"
//     accept() new connections
//     write/read() client sockets and handle request, send back response


Server::Server() {
    //set socket, port, password
}
Server::~Server() {
    //close socket if the fd exists
}

void Server::setSocket()
{
    int opt = 1;
    
    this->_socketFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (this->_socketFd == -1)
        throw std::runtime_error(std::string("Error: socket creation failed: ") + strerror(errno));
    
    if (setsockopt(this->_socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        throw std::runtime_error(std::string("Error: socket configuration failed: ") + strerror(errno));
    
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(static_cast<unsigned short>(this->_port));
    sin.sin_addr.s_addr = INADDR_ANY;
    if (::bind(this->_socketFd, reinterpret_cast<sockaddr*>(&sin), sizeof(sin)) == -1)
        throw std::runtime_error(std::string("Error: socket binding failed: ") + strerror(errno));

    if (::listen(this->_socketFd, 128) == -1)
        throw std::runtime_error(std::string("Error: socket listening failed: ") + strerror(errno));
}

void    Server::run()
{
    //create server handler
    //register it in event handler
    this->setSocket();
    //call server routine
}

