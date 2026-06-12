/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Status.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 08:03:07 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/12 10:50:32 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_HPP
# define STATUS_HPP

enum    Status {
    SUCCESS = 0,
    
    //rpl
    RPL_WELCOME = 001,
    RPL_TOPIC = 332,
    RPL_NAMREPLY = 353,
    RPL_ENDOFNAMES = 366,
    
    //command and registration
    ERR_NOTREGISTERED = 451,
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTERED = 462,

    //nickanme
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,

    //password
    ERR_PASSWDMISMATCH = 464,

    //channel
    ERR_NOSUCHCHANNEL = 403,
    ERR_USERNOTINCHANNEL = 441,
    ERR_NOTONCHANNEL = 442,
    ERR_CHANNELISFULL = 471,
    ERR_INVITEONLYCHAN = 473,
    ERR_BADCHANNELKEY = 475,
    ERR_CHANOPRIVSNEEDED = 482,
};

#endif