#include "include/controller/ThemeController.hpp"
#include "io/CommandParser.hpp"
#include <iostream>

std::string ThemeController::getKeyword() const {
    return "theme";
}

void ThemeController::execute(io::CommandHandle& cmd) {
    if (cmd->args.size() != 1) {
        std::cout << "Command 'theme' requires one string argument\n";
        return;
    };

    std::cout << "Executing command with: " << cmd->args[0] << "\n";
}
