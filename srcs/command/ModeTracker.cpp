/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeTracker.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 08:53:33 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/18 08:55:53 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command/ModeTracker.hpp"

ModeTracker::ModeTracker():
    addedModes(""),
    addedArgs(""),
    removedModes(""),
    removedArgs(""),
    totalArgModes(0),
    argIndex(1),
    currentSign(0),
    adding(false) {}