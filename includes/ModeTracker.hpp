/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeTracker.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 08:51:59 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/18 08:53:27 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODETRACKER_HPP
# define MODETRACKER_HPP

# include <string>

struct ModeTracker {
    std::string addedModes;
    std::string addedArgs;
    std::string removedModes;
    std::string removedArgs;
    size_t      totalArgModes;
    size_t      argIndex;
    char        currentSign;
    bool        adding;

    ModeTracker();
};

#endif