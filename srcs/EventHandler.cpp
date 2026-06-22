/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 07:58:40 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 10:45:10 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "EventHandler.hpp"
#include "EventLoop.hpp"
#include "ClientManager.hpp"
#include "CommandDispatcher.hpp"
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <sys/epoll.h>

EventHandler::EventHandler(EventLoop& loop, ClientManager& clients, ChannelManager& channels, CommandDispatcher& dispatcher) :
    _loop(loop),
    _clients(clients),
    _channels(channels),
    _dispatcher(dispatcher) {}

EventHandler::~EventHandler() {}

void EventHandler::onError(int fd)
{
    if (fd == -1)
        return ;
    if (epoll_ctl(this->_loop.getEpfd(), EPOLL_CTL_DEL, fd, NULL) == -1)
        std::cerr << "Warning: epoll interest list deregistration failed: " << strerror(errno) << std::endl;
    closeSocket(fd);
}

void EventHandler::closeSocket(int &fd)
{
    if (close(fd) == -1) {
        std::cerr << "Warning: socket closing failed: " << strerror(errno) << std::endl;
    }
    fd = -1;
}