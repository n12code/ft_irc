/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 07:27:25 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 07:54:06 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"
#include <stdexcept>
#include <cerrno>
#include <cstring>


EventLoop::EventLoop() {}
EventLoop::~EventLoop() {}

void EventLoop::InitLoop()
{
    this->_epfd = epoll_create1(0);
    if (this->_epfd == -1)
        throw std::runtime_error(std::string("Error: epoll instance creation failed: ") + strerror(errno));
}

void EventLoop::registerHandler(const int fd, EventHandler* handler)
{
    this->_handlers[fd] = handler;
    this->_ev.events = EPOLLIN;
    this->_ev.data.fd = fd;
    if (epoll_ctl(this->_epfd, EPOLL_CTL_ADD, fd, &this->_ev) == -1)
        throw std::runtime_error(std::string("Error: epoll interest list registration failed: ") + strerror(errno));
}

void EventLoop::serverRoutine()
{
    for (;;) {
        int nfds = epoll_wait(this->_epfd, this->_events, 1024, -1);
        if (nfds == -1)
            throw std::runtime_error(std::string("Error: epoll wait failed: ") + strerror(errno));
        for (int i = 0; i < nfds; i++)
        {
            int fd = this->_events[i].data.fd;
            if (this->_events[i].events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
                this->_handlers[fd]->onError(fd);
            }
            else if (this->_events[i].events & EPOLLIN) {
                this->_handlers[fd]->onReadable(fd);
            }
        }
    }    
}