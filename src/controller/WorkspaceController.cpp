#include "include/controller/WorkspaceController.hpp"
#include "io/CommandParser.hpp"
#include "util/MonitorUtil.hpp"
#include "util/ShellUtil.hpp"
#include <cassert>
#include <iostream>
#include <ostream>
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
    } else if (cmd->args[0] == "send") { 
        if (cmd->args.size() < 2) {
            throw std::runtime_error("Expected at least two arguments for command " + getKeyword() + " send");
        }
        sendWindow(io::CommandParser::parseIntArg(cmd->args[1]));
    } else if (cmd->args[0] == "mvleft") { 
        moveWindow(-1);
    } else if (cmd->args[0] == "mvright") { 
        moveWindow(1);
    } else {
        throw std::runtime_error("Command " + getKeyword() + " " + cmd->args[0] + " does not exist!");
    }
}

void WorkspaceController::switchWorkspace(uint32_t target_virtual) const {
    for (uint32_t i = 0; i < monitor_names.size(); i++) {
        ShellUtil::executeShellCommand(std::string(HYPR_CTL) + " dispatch workspace " + std::to_string(i + 1) + std::to_string(target_virtual));
    }
}

void WorkspaceController::sendWindow(uint32_t target_virtual) const {
    std::string active_window = getActiveWindowId();
    // Workspace workspace = getCurrentWorkspace();
    std::cout << active_window << std::endl;

    std::string s = ShellUtil::executeShellCommand(std::string(HYPR_CTL) + " activeworkspace -j | jq -r '.id'");
    std::cout << s << std::endl;
    // ShellUtil::executeShellCommand(std::string(HYPR_CTL) + " dispatch movetoworkspacesilent " + std::to_string(workspace.physical_id) + std::to_string(target_virtual) + ",address:" + active_window);
}

void WorkspaceController::moveWindow(int32_t physical_delta) const {
    assert(physical_delta == -1 || physical_delta == 1);
    std::string active_window = getActiveWindowId(); 
    Workspace workspace = getCurrentWorkspace();
    int32_t physical_id = workspace.physical_id + physical_delta; // monitors are 1 indexed
    physical_id = physical_id == 0 ? monitor_names.size() : physical_id;
    physical_id = physical_id > monitor_names.size() ? 1 : physical_id;
    ShellUtil::executeShellCommand(std::string(HYPR_CTL) + " dispatch movetoworkspacesilent " + std::to_string(physical_id) + std::to_string(workspace.virtual_id) + ",address:" + active_window);
}

WorkspaceController::Workspace WorkspaceController::getCurrentWorkspace() const {
    uint32_t workspace = ShellUtil::parseStringToInt(ShellUtil::executeShellCommand(std::string(HYPR_CTL) + " activeworkspace -j | jq -r '.id'"));
    return {workspace / 10, workspace % 10};
}

std::string WorkspaceController::getActiveWindowId() const {
    return ShellUtil::executeShellCommand(std::string(HYPR_CTL) + " activewindow -j | jq -r '.address'");
}
