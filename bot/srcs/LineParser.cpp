ParseLine Bot::parseLine(const std::string& line)
{
    ParseLine  result;
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

void Bot::handleIncoming(const char* data, ssize_t len)
{
    this->_readBuffer.append(data, len);
    
    size_t pos;
    while ((pos = this->_readBuffer.find('\n')) != std::string::npos)
    {
        std::string line = this->_readBuffer.substr(0, pos);
        this->_readBuffer.erase(0, pos + 1);
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);
        ParseLine parsed = this->parseLine(line);
        std::cout << parsed.prefix << std::endl;
        std::cout << parsed.command << std::endl;
        for (size_t i = 0; parsed.params.size() > i; i++)
            std::cout << parsed.params[i] << std::endl;
        if (parsed.hasTrailing)
            std::cout << parsed.trailing << std::endl;
        std::cout << line << std::endl;
    }
}
