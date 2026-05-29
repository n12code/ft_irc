/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/29 08:11:54 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClientHandler.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <sys/epoll.h>

ClientHandler::ClientHandler(EventLoop &loop) : EventHandler(loop) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::onError(int fd)
{
    EventHandler::onError(fd);
    //remove from channels
    //remove from clients
}

void ClientHandler::onReadable(const int fd)
{
    (void)fd;
}
