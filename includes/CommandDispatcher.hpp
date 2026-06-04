/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 08:27:45 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/04 09:08:04 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDDISPATCHER_HPP
# define COMMANDDISPATCHER_HPP

# include <map>
# include <string>

class Message;
class Command;

class CommandDispatcher
{
    private:
        std::map<std::string, Command> _commands;
    public:
        CommandDispatcher();
        ~CommandDispatcher();

        void    dispatch(Message& msg);
};

#endif