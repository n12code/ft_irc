/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 07:41:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/01 10:46:47 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "EventLoop.hpp"
# include "ClientManager.hpp"
# include <sys/epoll.h>
# include <string>

class Server
{
    private:
        int             _socketFd;
        unsigned short  _port;
        std::string     _pswd;
        
        EventLoop       _loop;
        ClientManager   _clients;
        
    public:
        Server(const unsigned short, const std::string pswd);
        ~Server();
        
        void    run();
        void    setSocket();
};

#endif