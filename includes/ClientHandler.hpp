/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 10:46:17 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTHANDLER_HPP
# define CLIENTHANDLER_HPP

# include "EventHandler.hpp"
# include "ClientManager.hpp"
# include "CommandDispatcher.hpp"

class EventLoop;

class ClientHandler : public EventHandler
{
    public:
        ClientHandler(EventLoop& loop, ClientManager& clients, ChannelManager& channels, CommandDispatcher& dispatcher);
        ~ClientHandler();

        void    onReadable(const int fd);
        void    onError(int fd);
};

#endif