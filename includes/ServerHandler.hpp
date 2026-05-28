/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 09:02:35 by nbodin           ###   ########lyon.fr   */
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

        void onError(const int fd);
        void onReadable(const int fd);
};

#endif