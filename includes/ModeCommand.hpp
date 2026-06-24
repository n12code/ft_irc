/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:30:31 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/24 09:49:24 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"
# include "ModeTracker.hpp"

class Channel;
class Client;

class ModeCommand : public Command
{
    public:
        ModeCommand(const CommandContext& context);
        ~ModeCommand();

        void    execute();
        void    sendChannelModes(Client& client, const Channel& chan);
        int     getClientFd(const std::string& arg, Client& client, const Channel& chan);
        int     handleParamModes(const char c, const std::vector<std::string>& params, Client& client, Channel& chan, ModeTracker& tracker);
        void    appendModeAndArg(ModeTracker& tracker, char sign, char mode, const std::string& arg = "");
        void    sendModeMessage(const ModeTracker& tracker, const Client& client, const Channel& chan);
};

#endif