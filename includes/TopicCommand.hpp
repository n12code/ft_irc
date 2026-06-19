/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 09:52:32 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/19 10:06:24 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICCOMMAND_HPP
# define TOPICCOMMAND_HPP

# include "Command.hpp"
# include "CommandContext.hpp"

class TopicCommand : public Command
{
    public:
        TopicCommand(const CommandContext& context);
        ~TopicCommand();

        void    execute();
        bool    isJustSpaces(const std::string& str) const;
};

#endif