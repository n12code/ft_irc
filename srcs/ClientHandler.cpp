/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 10:59:16 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClientHandler.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <sys/epoll.h>

ClientHandler::ClientHandler(EventLoop&  loop) :
    _loop(loop) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::closeSocket(int &fd)
{
    if (close(fd) == -1) {
        std::cerr << "Warning: socket closing failed: " << strerror(errno) << std::endl;
    }
    fd = -1;
}

void ClientHandler::onError(int fd)
{
    if (fd == -1)
        return ;
    if (epoll_ctl(this->_loop.getEpfd(), EPOLL_CTL_DEL, fd, NULL) == -1)
        std::cerr << "Warning: epoll interest list deregistration failed: " << strerror(errno) << std::endl;
    closeSocket(fd);
    //remove from channels
    //remove from clients
}


void ClientHandler::onReadable(const int fd)
{
    (void)fd;
}
