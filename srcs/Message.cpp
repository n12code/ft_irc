/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:41:17 by nbodin            #+#    #+#             */
/*   Updated: 2026/09/04 07:31:06 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "Client.hpp"
#include "ClientManager.hpp"
#include <string>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <vector>
#include <cstring>


Message::Message(ClientManager& clients):
    _clients(clients),
    _command(""),
    _params() {}

Message::~Message() {}

bool    Message::readMessage(int fd)
{
    char    buf[4096];
    try {
        Client& client = this->_clients.getClientWithFd(fd);
        int bytes = read(fd, buf, sizeof(buf));
        if (bytes > 0)
        {
            client.appendToBuffer(client.getBuffer(), std::string(buf, bytes));
            return (true);
        }
        else if (bytes == 0)
        {
            std::cerr << "Warning: client (fd:" << client.getFd() << ") connection closed" << std::endl;
            return (false);
        }
        else
        {
            std::cerr << "Warning: error while reading client (fd:" << client.getFd() << ")" << std::endl;
            return (false);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return (false);
}

std::string  Message::extractMessage(std::string& buffer)
{
    size_t pos = buffer.find("\n");
    if (pos == std::string::npos)
        return ("");
    std::string message = buffer.substr(0, pos);
    buffer.erase(0, pos + 1);
    if (!message.empty() && message[message.size() - 1] == '\r')
        message.erase(message.size() - 1);
    return (message);
}

void Message::extractCommand(std::string message)
{
    size_t  pos = message.find(' ');
    if (pos == std::string::npos)
    {
        this->_command = message;
        return ;
    }
    this->_command = message.substr(0, pos);
}

void Message::extractParams(std::string message)
{
    size_t  pos = message.find(' ');
    if (pos == std::string::npos)
        return ;
    for (;;)
    { 
        pos = message.find_first_not_of(' ', pos);
        if (pos == std::string::npos)
            return ;
        if (this->_params.size() == 14)
        {
            if (message[pos] == ':')
                this->_params.push_back(message.substr(pos + 1));
            else
                this->_params.push_back(message.substr(pos));
            return;
        }
        if (message[pos] == ':')
        {
            this->_params.push_back(message.substr(pos + 1));
            return ;
        }
        size_t nextSpace = message.find(' ', pos);
        if (nextSpace == std::string::npos)
        {
            this->_params.push_back(message.substr(pos));
            return ;
        }
        this->_params.push_back(message.substr(pos, nextSpace - pos));
        pos = nextSpace;
    }
}

void    Message::removeSpecialChars(std::string& message)
{
    for (size_t i = 0; i < message.size(); ++i)
    {
        if (message[i] == '\0' || message[i] == '\r')
            message.erase(i, 1);
    }
}

bool    Message::parseMessage(std::string& buffer)
{
    std::string message = this->extractMessage(buffer);
    if (message.empty())
        return (false);
    this->removeSpecialChars(message);
    this->extractCommand(message);
    this->extractParams(message);

    return (true);
}

void Message::clearParsedData()
{
    this->_command.clear();
    this->_params.clear();
}

std::string& Message::getCommand()
{
    return (this->_command);
}

std::vector<std::string>&    Message::getParams()
{
    return (this->_params);
}

void Message::setParams(const std::vector<std::string> params)
{
    this->_params = params;
}
