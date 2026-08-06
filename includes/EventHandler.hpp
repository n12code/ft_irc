/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 10:54:21 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/24 08:59:42 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include "EventLoop.hpp"
# include "ClientManager.hpp"
# include "ChannelManager.hpp"
# include "command/CommandDispatcher.hpp"

class EventHandler
{
    protected:
        EventLoop&          _loop;
        ClientManager&      _clients;
        ChannelManager&     _channels;
        CommandDispatcher&  _dispatcher;
    public:
        EventHandler(EventLoop& loop, ClientManager& clients, ChannelManager& channels, CommandDispatcher& dispatcher);
        virtual ~EventHandler();

        virtual void onReadable(int& fd) = 0;
        virtual void onWritable(int& fd);
        virtual void onError(int& fd);
        virtual void closeSocket(int& fd);
};

#endif