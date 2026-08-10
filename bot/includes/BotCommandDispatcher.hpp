class BotDispatcher
{
private:
    std::map<std::string, BotCommandCreator> _commands;

public:
    BotDispatcher();
    void dispatch(Bot& bot, const ParsedLine& parsed);
};