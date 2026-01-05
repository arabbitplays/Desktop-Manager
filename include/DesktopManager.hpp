#ifndef DESKTOP_MANAGER
#define DESKTOP_MANAGER

#include <memory>
#include <controller/IController.hpp>
#include <vector>

class DesktopManager {
public:
    DesktopManager() = default;
    ~DesktopManager() = default;

    void init();
    void run();

    void activateDevMode();
private:
    bool dev_mode_active = false;
    std::vector<std::shared_ptr<IController>> controllers;
};

#endif // DESKTOP_MANAGER

