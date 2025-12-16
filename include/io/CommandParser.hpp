#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include <sys/socket.h>
#include <vector>
#include <memory>
#include <string>

namespace io {
    struct Command;
    typedef std::shared_ptr<Command> CommandHandle;
    struct Command {
        std::string keyword;
        std::vector<std::string> args;
    };

    class CommandParser {
    public:
        CommandParser() = default;
        std::shared_ptr<Command> parseCommand(const std::string& raw);
    };
}

#endif 
