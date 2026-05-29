/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 07:20:01 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/29 08:19:21 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTLOOP_HPP
# define EVENTLOOP_HPP

# include <sys/epoll.h>
# include <map>

class EventHandler;

class EventLoop
{
    private:
        int                             _epfd;
        epoll_event                     _ev;
        epoll_event                     _events[1024];
        std::map<int, EventHandler*>    _handlers;
        
    public:
        EventLoop();
        ~EventLoop();

        void    initLoop();
        void    registerHandler(const int fd, EventHandler* handler);
        void    serverRoutine();

        // getter
        int     getEpfd(); 
};


#endif
