/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:41:17 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/02 10:39:21 by nbodin           ###   ########lyon.fr   */
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

bool    Message::readMessage(int fd)
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

std::string  Message::extractMessage(std::string& buffer)
{
    int pos = buffer.find("\n");
    if (pos == std::string::npos)
        return ("");
    std::string message = buffer.substr(0, pos);
    buffer.erase(0, pos + 1);
    if (message.size() == 1)
        return ("");
    message.erase(message.size() - 1);
    return (message);
}

std::string Message::extractSrc(std::string message)
{
    return std::string();
}

std::string Message::extractCmd(std::string message)
{
    return std::string();
}

std::string Message::extractParams(std::string message)
{
    return std::string();
}

bool    Message::parseMessage(std::string& buffer)
{
    std::string message = this->extractMessage(buffer);
    if (message.empty())
        return (false);
    extractSrc();
}