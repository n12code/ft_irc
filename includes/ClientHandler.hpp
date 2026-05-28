/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 10:58:09 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTHANDLER_HPP
# define CLIENTHANDLER_HPP

# include "EventHandler.hpp"
# include "EventLoop.hpp"

class ClientHandler : public EventHandler
{
    private:
        EventLoop&  _loop;
    public:
        ClientHandler(EventLoop&  loop);
        ~ClientHandler();

        void    onReadable(const int fd);
        void    onError(int fd);
        void    closeSocket(int& fd);
};

#endif