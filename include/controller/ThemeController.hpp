#ifndef THEME_CONTROLLER
#define THEME_CONTROLLER

#include <string>
#include "io/CommandParser.hpp"
#include <controller/IController.hpp>
#include <unordered_map>
#include <vector>

class ThemeController : public IController {
public:
    struct Theme {
        std::string wallpaper_name;
        std::string kitty_theme;
        std::string nvim_theme;
        std::string hypr_theme;
        std::string waybar_theme;
    };

    ThemeController();
    ~ThemeController() = default;

    std::string getKeyword() const override;
    std::string execute(io::CommandHandle& cmd) override;

private:
    static constexpr char* WALLPAPER_DIR = "~/Resources/Wallpapers";
    static constexpr char* KITTY_THEME_FILE = "~/.config/kitty/current-theme.conf";
    static constexpr char* KITTY_THEME_DIR = "~/.config/kitty/themes";
    static constexpr char* NVIM_THEME_FILE = "~/.config/nvim/current-theme";
    static constexpr char* HYPR_THEME_FILE = "~/.config/hypr/config/current-theme.conf";
    static constexpr char* HYPR_THEME_DIR = "~/.config/hypr/themes";
    static constexpr char* WAYBAR_THEME_FILE = "~/.config/waybar/current-theme.css";
    static constexpr char* WAYBAR_THEME_DIR = "~/.config/waybar/themes";

    static constexpr char* SWWW_OPTIONS = "--transition-type outer --transition-pos top-right --resize crop --transition-bezier=0.1,0.2,0.4,1.0 --transition-fps=60";

    void setWallpaperAll(const std::string& name);
    void setWallpaper(const std::string name, const std::string& montor_name) const;
    void setKittyTheme(const std::string& name);
    void setNvimTheme(const std::string& name);
    void setHyprTheme(const std::string& name);
    void setWaybarTheme(const std::string& name);

    std::vector<std::string> monitor_names;
    std::unordered_map<std::string, Theme> themes;
};

#endif // THEME_CONTROLLER

