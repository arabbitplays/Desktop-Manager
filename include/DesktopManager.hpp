#ifndef DESKTOP_MANAGER
#define DESKTOP_MANAGER

#include "controller/ThemeController.hpp"
#include <memory>
class DesktopManager {
public:
    DesktopManager() = default;
    ~DesktopManager() = default;

    void init();
    void run();
private:
    std::shared_ptr<ThemeController> theme_controller;
};

#endif // DESKTOP_MANAGER

