/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:47:06 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/11 10:38:12 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include <string>
# include <map>

class Channel;

class ChannelManager
{
    private:
        std::map<std::string, Channel>  _channels;
    public:
        ChannelManager();
        ~ChannelManager(); 
        
        Channel&    getChannelByName(const std::string& name);
        bool        hasChannel(const std::string& name);

        Channel&    createChannel(const std::string& name, const int creatorFd);
        void        addChannel(Channel channel);
        void        removeChannel(const std::string& name);

        std::vector<std::string>& getChannelsOfUser(const int clientFd);
};

#endif