#include "LineParser.hpp"

ParsedLine parseLine(const std::string& line)
{
    ParsedLine  result;
    size_t      pos = 0;

    if (!line.empty() && line[0] == ':')
    {
        size_t space = line.find(' ');
        if (space == std::string::npos)
            return (result);
        result.prefix = line.substr(1, space - 1);
        pos = space + 1;
    }

    size_t space = line.find(' ', pos);
    if (space == std::string::npos)
    {
        result.command = line.substr(pos);
        return (result);
    }
    result.command = line.substr(pos, space - pos);
    pos = space + 1;

    for (;;)
    {
        pos = line.find_first_not_of(' ', pos);
        if (pos == std::string::npos)
            break;
        if (line[pos] == ':')
        {
            result.hasTrailing = true;
            result.trailing = line.substr(pos + 1);
            break;
        }
        size_t nextSpace = line.find(' ', pos);
        if (nextSpace == std::string::npos)
        {
            result.params.push_back(line.substr(pos));
            break;
        }
        result.params.push_back(line.substr(pos, nextSpace - pos));
        pos = nextSpace;
    }
    return (result);
}

std::string extractNick(const std::string& prefix)
{
    size_t excl = prefix.find('!');
    if (excl == std::string::npos)
        return (prefix);
    return (prefix.substr(0, excl));
}

std::vector<std::string> extractArgs(const std::string& text, size_t afterCmdPos)
{
    std::vector<std::string> args;
    size_t pos = afterCmdPos;

    for (;;)
    {
        pos = text.find_first_not_of(' ', pos);
        if (pos == std::string::npos)
            break;
        size_t nextSpace = text.find(' ', pos);
        if (nextSpace == std::string::npos)
        {
            args.push_back(text.substr(pos));
            break;
        }
        args.push_back(text.substr(pos, nextSpace - pos));
        pos = nextSpace;
    }
    return (args);
}