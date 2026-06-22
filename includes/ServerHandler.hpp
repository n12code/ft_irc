/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/22 10:42:42 by nbodin           ###   ########lyon.fr   */
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
        ServerHandler(EventLoop& loop, ClientManager& clients, CommandDispatcher& dispatcher);
        ~ServerHandler();

        void    onReadable(const int fd);
        void    onError(int fd);
};

#endif