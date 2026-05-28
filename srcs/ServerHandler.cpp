/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:53 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 09:03:39 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"

ServerHandler::ServerHandler(EventLoop &loop) :
    _loop(loop) {}

ServerHandler::~ServerHandler()
{
}

void ServerHandler::onError(const int fd)
{
}

void ServerHandler::onReadable(const int fd)
{
}
