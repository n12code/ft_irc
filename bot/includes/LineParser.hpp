#ifndef LINEPARSER_HPP
#define LINEPARSER_HPP

#include <string>
#include <vector>

struct ParsedLine
{
    std::string                 prefix;
    std::string                 command;
    std::vector<std::string>    params;
    bool                        hasTrailing;
    std::string                 trailing;
    ParsedLine() : hasTrailing(false){}
};

ParsedLine                  parseLine(const std::string& line);
std::string                 extractNick(const std::string& prefix);
std::vector<std::string>    extractArgs(const std::string& text, size_t afterCmdPos);

#endif