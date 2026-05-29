/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 10:54:21 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/29 08:14:46 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

# include "EventLoop.hpp"

class EventHandler
{
    protected:
        EventLoop&  _loop;
    public:
        EventHandler(EventLoop& loop);
        virtual ~EventHandler();

        virtual void onReadable(const int fd) = 0;
        virtual void onError(int fd);
        virtual void closeSocket(int& fd);
};

#endif