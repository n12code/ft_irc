/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:30:31 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/17 10:51:09 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"

class Channel;
class Client;

class ModeCommand : public Command
{
    public:
        ModeCommand(const CommandContext& context);
        ~ModeCommand();

        void    execute();
        void    sendChannelModes(const Client& client, const Channel& chan);
        int     getClientFd(const std::string& arg, const Client& client, const Channel& chan);
        int     handleParamModes(size_t& totalArgModes, size_t& paramIdx, const bool adding, const char c, const std::vector<std::string>& params, const Client& client, Channel& chan);


};

#endif