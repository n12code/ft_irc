#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP

#include <string>
#include <vector>

class Bot;

std::string cmdPing(Bot& bot, const std::vector<std::string>& args);

#endif