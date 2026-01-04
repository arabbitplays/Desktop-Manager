#ifndef THEME_CONTROLLER
#define THEME_CONTROLLER

#include <string>
#include "io/CommandParser.hpp"
#include <controller/IController.hpp>
#include <vector>

class ThemeController : public IController {
public:
    ThemeController();
    ~ThemeController() = default;

    std::string getKeyword() const override;
    void execute(io::CommandHandle& cmd) override;

private:
    static constexpr char* WALLPAPER_DIR = "~/Resources/Wallpapers";

    void setWallpaperAll(const std::string& name);
    void setWallpaper(const std::string name, const std::string& montor_name) const;

    std::vector<std::string> monitor_names;
};

#endif // THEME_CONTROLLER

