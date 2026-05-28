/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:24:10 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/27 11:31:09 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTHANDLER_HPP
# define CLIENTHANDLER_HPP

# include "EventHandler.hpp"

class ClientHandler : public EventHandler
{
    private:
        
    public:
        ClientHandler();
        ~ClientHandler();

        void onError(const int fd);
        void onReadable(const int fd);
};

#endif