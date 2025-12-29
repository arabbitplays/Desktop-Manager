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
private:
    std::vector<std::shared_ptr<IController>> controllers;
};

#endif // DESKTOP_MANAGER

