/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/29 08:22:26 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERHANDLER_HPP
# define SERVERHANDLER_HPP

# include "EventHandler.hpp"

class EventLoop;

class ServerHandler : public EventHandler
{
    public:
        ServerHandler(EventLoop& loop);
        ~ServerHandler();

        void    onReadable(const int fd);
        void    onError(int fd);
};

#endif