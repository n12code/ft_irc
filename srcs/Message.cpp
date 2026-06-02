/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:41:17 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/02 08:28:32 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Client.hpp"
#include "ClientManager.hpp"
#include <string>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>

Message::Message(ClientManager& clients):
    _clients(clients) {}

Message::~Message() {}

bool Message::readMessage(int fd)
{
    char    buf[4096];
    try {
        Client& client = this->_clients.getClientWithFd(fd);
        for (;;)
        {
            int bytes = read(fd, buf, sizeof(buf));
            if (bytes > 0)
                client.getBuffer() += std::string(buf, bytes);
            else if (bytes == 0)
            {
                std::cerr << "Warning: client (fd:" << client.getFd() << ") connection closed" << std::endl;
                return (false);
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    return (true);
                else
                {
                    std::cerr << "Warning: error while reading client (fd:" << client.getFd() << "): " << strerror(errno) << std::endl;
                    return (false);
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return (false);
}