/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 07:41:49 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 09:02:28 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/epoll.h>
# include "EventLoop.hpp"

class Server
{
    private:
        int             _socketFd;
        unsigned short  _port;
        std::string     _pswd;
        
        EventLoop       _loop;
        
    public:
        Server(const unsigned short, const std::string pswd);
        ~Server();
        
        void    run();
        void    setSocket();
};

#endif