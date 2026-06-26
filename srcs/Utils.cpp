/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbodin <nbodin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:58:04 by nbodin            #+#    #+#             */
/*   Updated: 2026/06/26 09:00:54 by nbodin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

void Utils::toLowerIrc(std::string& string)
{
    for (size_t i = 0; i < string.size(); ++i)
    {
        if ('A' <= string[i] && string[i] <= 'Z')
            string[i] = string[i] + 32;
        else if (string[i] == '[') 
            string[i] = '{';
        else if (string[i] == ']') 
            string[i] = '}';
        else if (string[i] == '\\')
            string[i] = '|';
        else if (string[i] == '~') 
            string[i] = '^';
    }
}