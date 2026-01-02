#include "include/controller/WorkspaceController.hpp"
#include "io/CommandParser.hpp"
#include "util/MonitorUtil.hpp"
#include "util/ShellUtil.hpp"
#include <stdexcept>
#include <string>

WorkspaceController::WorkspaceController() {
    monitor_names = MonitorUtil::getMonitorNamesForCurrSystem(); 
}

std::string WorkspaceController::getKeyword() const {
    return "workspace";
}

void WorkspaceController::execute(io::CommandHandle &cmd) {
    if (cmd->args.size() < 1) {
        throw std::runtime_error("Expected at least one argument for command " + getKeyword());
    }

    if (cmd->args[0] == "switch") { 
        if (cmd->args.size() < 2) {
            throw std::runtime_error("Expected at least two arguments for command " + getKeyword() + " switch");
        }

        switchWorkspace(io::CommandParser::parseIntArg(cmd->args[1]));
    }
}

void WorkspaceController::switchWorkspace(uint32_t target_virtual) const {
    for (uint32_t i = 0; i < monitor_names.size(); i++) {
        ShellUtil::executeShellCommand("/run/current-system/sw/bin/hyprctl dispatch workspace " + std::to_string(i + 1) + std::to_string(target_virtual));
    }
}

