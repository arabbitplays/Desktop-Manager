#include "include/io/CommandParser.hpp"
#include <iostream>
#include <cassert>

namespace io {
    std::vector<std::string> splitAt(const std::string& input, char sep) {
        std::vector<std::string> result{};
        std::string curr_sub_str = "";
        for (char c : input) {
            if (c == sep || c == '\n') {
                if (curr_sub_str.empty())
                    continue;
                result.push_back(curr_sub_str);
                curr_sub_str.clear();
            } else {
                curr_sub_str += c;
            }
        }  
        return result;
    }

    std::shared_ptr<Command> CommandParser::parseCommand(const std::string& raw) {
        auto cmd = std::make_shared<Command>();
        std::vector<std::string> parts = splitAt(raw, ' ');
        assert(parts.size() > 0);
        cmd->keyword = parts.front();
        cmd->args.assign(parts.begin() + 1, parts.end());
        return cmd;
    }
}
