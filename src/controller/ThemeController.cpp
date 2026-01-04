#include "include/controller/ThemeController.hpp"
#include "io/CommandParser.hpp"
#include "util/MonitorUtil.hpp"
#include "util/ShellUtil.hpp"
#include <iostream>

ThemeController::ThemeController() {
    monitor_names = MonitorUtil::getMonitorNamesForCurrSystem();
}

std::string ThemeController::getKeyword() const {
    return "theme";
}

void ThemeController::execute(io::CommandHandle& cmd) {
    if (cmd->args.size() != 1) {
        std::cout << "Command 'theme' requires one string argument\n";
        return;
    };

    std::string theme_name = cmd->args[0];
    if (theme_name == "tokyo") {
        setWallpaperAll("tokyo_night.jpg");
    } else if (theme_name == "forest") {
        setWallpaperAll("nier.jpg");
    } else {
        throw std::runtime_error("Command " + getKeyword() + " " + cmd->args[0] + " does not exist!");
    }
}

void ThemeController::setWallpaperAll(const std::string& name) {
    for (const auto& monitor : monitor_names) {
        setWallpaper(name, monitor);
    }
}

void ThemeController::setWallpaper(const std::string name, const std::string& monitor_name) const {
    ShellUtil::executeShellCommand("swww img " + std::string(WALLPAPER_DIR) + "/" + name + " --transition-type outer --transition-pos top-right -o " + monitor_name + " --resize crop");
} 
