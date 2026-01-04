#include "include/controller/ThemeController.hpp"
#include "io/CommandParser.hpp"
#include "util/MonitorUtil.hpp"
#include "util/ShellUtil.hpp"
#include "util/FileUtil.hpp"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

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
        setKittyTheme("tokyo_night.conf");
        setNvimTheme(theme_name);
        setWallpaperAll("tokyo_night.jpg");
    } else if (theme_name == "forest") {
        setKittyTheme("gruvbox_dark.conf");
        setWallpaperAll("nier.jpg");
        setNvimTheme(theme_name);
    } else {
        throw std::runtime_error("Command " + getKeyword() + " " + cmd->args[0] + " does not exist!");
    }
}

void ThemeController::setWallpaperAll(const std::string& name) {
    std::string output = ShellUtil::executeShellCommand("swww img " + std::string(WALLPAPER_DIR) + "/" + name + " " + std::string(SWWW_OPTIONS));
    ShellUtil::printShellOutput(output);
}

void ThemeController::setWallpaper(const std::string name, const std::string& monitor_name) const {
    std::string output = ShellUtil::executeShellCommand("swww img " + std::string(WALLPAPER_DIR) + "/" + name + " " + std::string (SWWW_OPTIONS) + " -o " + monitor_name);
    ShellUtil::printShellOutput(output);
} 

void ThemeController::setKittyTheme(const std::string& name) {
    std::string src = std::string(KITTY_THEME_DIR) + "/" + name;
    std::string dst = std::string(KITTY_THEME_FILE);
    FileUtil::copyFile(src, dst);    
    std::string output = ShellUtil::executeShellCommand("kill -USR1 $(pidof kitty)");
    ShellUtil::printShellOutput(output);
}

void ThemeController::setNvimTheme(const std::string& name) {
    FileUtil::overwriteFile(std::string(NVIM_THEME_FILE), name);
}
