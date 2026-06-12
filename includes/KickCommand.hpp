/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 08:25:35 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/12 10:21:48 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"

class KickCommand : public Command
{
    public:
        KickCommand(const CommandContext& context);
        ~KickCommand();

        void    execute();
        void    handleOneChannel(const std::vector<std::string>& channels, const std::vector<std::string>& users, const std::string& comment);
        void    handleManyChannels(const std::vector<std::string>& channels, const std::vector<std::string>& users, const std::string& comment);
};



#endif