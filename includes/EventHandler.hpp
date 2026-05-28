/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 10:54:21 by nbodin            #+#    #+#             */
/*   Updated: 2026/05/28 09:14:07 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTHANDLER_HPP
# define EVENTHANDLER_HPP

class EventHandler
{
    public:
        virtual ~EventHandler() {};

        virtual void onError(const int fd) = 0;
        virtual void onReadable(const int fd) = 0;
};

#endif