/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 10:54:21 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 08:35:25 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include "EventLoop.hpp"
# include "ClientManager.hpp"
# include "CommandDispatcher.hpp"

class EventHandler
{
    protected:
        EventLoop&          _loop;
        ClientManager&      _clients;
        CommandDispatcher&  _dispatcher;
    public:
        EventHandler(EventLoop& loop, ClientManager& clients, CommandDispatcher& dispatcher);
        virtual ~EventHandler();

        virtual void onReadable(const int fd) = 0;
        virtual void onError(int fd);
        virtual void closeSocket(int& fd);
};

#endif