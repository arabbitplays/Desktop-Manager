#ifndef THEME_CONTROLLER
#define THEME_CONTROLLER

#include <string>
#include "io/CommandParser.hpp"
#include <controller/IController.hpp>
#include <vector>

class ThemeController : public IController {
public:
    struct Theme {
        std::string wallpaper_name;
        std::string kitty_theme;
        std::string nvim_theme;
    };

    ThemeController();
    ~ThemeController() = default;

    std::string getKeyword() const override;
    void execute(io::CommandHandle& cmd) override;

private:
    static constexpr char* WALLPAPER_DIR = "~/Resources/Wallpapers";
    static constexpr char* KITTY_THEME_FILE = "~/.config/kitty/current-theme.conf";
    static constexpr char* KITTY_THEME_DIR = "~/.config/kitty/themes";
    static constexpr char* NVIM_THEME_FILE = "~/.config/nvim/current-theme";

    static constexpr char* SWWW_OPTIONS = "--transition-type outer --transition-pos top-right --resize crop";

    void setWallpaperAll(const std::string& name);
    void setWallpaper(const std::string name, const std::string& montor_name) const;
    void setKittyTheme(const std::string& name);
    void setNvimTheme(const std::string& name);

    std::vector<std::string> monitor_names;
};

#endif // THEME_CONTROLLER

