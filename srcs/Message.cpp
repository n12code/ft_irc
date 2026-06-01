/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:41:17 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/01 12:09:46 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include <string>
#include <unistd.h>

Message::Message() {}

Message::~Message() {}

std::string Message::readMessage(int fd)
{
    char    buf[4096];
    try {
        int bytes = read(fd, buf, sizeof(buf));
        if (bytes > 0)
        {
            //append
        }
        else if (bytes == 0)
        {
            //eof
            //close connection
            //remove from epoll
            //remove from clients
            //remove from channels
            //onError() ?
        }
        else
        {
            //error
            //eagain ewouldblock
            //onError() ?
        }
    }
    catch () {
        
    }
}