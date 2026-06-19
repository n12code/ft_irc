/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:57:18 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/19 08:32:19 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <set>
# include <string>
# include "ClientManager.hpp"

class Channel
{
    private:
        std::string     _name;
        std::string     _topic;
        std::string     _password;
        size_t          _maxCap;
        std::set<char>  _modes;
        std::set<int>   _chanops;
        std::set<int>   _users;
        std::set<int>   _invited;
    public:
        Channel();
        Channel(const std::string& name, const int creatorFd);
        ~Channel();

        //getter
        const std::string       getPassword() const;
        const std::string       getName() const;
        const std::string       getTopic() const;
        size_t                  getMaxCap() const;
        const std::set<int>&    getUsers() const;
        const std::set<int>&    getInvited() const;
        
        //setter
        void    setPassword(const std::string& password);
        void    setMaxCap(const size_t& maxCap);
        
        //utility
        bool    hasMode(const char mode) const;
        bool    isInvited(const int fd) const;
        bool    isChanop(const int fd) const;
        bool    isUser(const int fd) const;
        void    addMode(const char mode);
        void    removeMode(const char mode);
        void    addInvited(const int fd);
        void    removeInvited(const int fd);
        void    addChanop(const int fd);
        void    removeChanop(const int fd);
        void    addUser(const int fd);
        void    removeUser(const int fd);
        void    sendToChannel(const std::string& message, ClientManager& clients) const;
};

#endif