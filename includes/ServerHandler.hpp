/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/23 07:49:57 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERHANDLER_HPP
# define SERVERHANDLER_HPP

# include "EventHandler.hpp"
# include "ClientManager.hpp"

class EventLoop;

class ServerHandler : public EventHandler
{
    public:
        ServerHandler(EventLoop& loop, ClientManager& clients, ChannelManager& channels, CommandDispatcher& dispatcher);
        ~ServerHandler();

        void    onReadable(int& fd);
        void    onError(int& fd);
};

#endif