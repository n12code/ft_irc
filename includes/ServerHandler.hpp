/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 10:52:36 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERHANDLER_HPP
# define SERVERHANDLER_HPP

# include "EventHandler.hpp"
# include "EventLoop.hpp"

class ServerHandler : public EventHandler
{
    private:
        EventLoop&  _loop;
    public:
        ServerHandler(EventLoop& loop);
        ~ServerHandler();

        void    onReadable(const int fd);
        void    onError(int fd);
        void    closeSocket(int& fd);
};

#endif