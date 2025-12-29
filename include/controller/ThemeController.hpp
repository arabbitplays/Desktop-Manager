#ifndef THEME_CONTROLLER
#define THEME_CONTROLLER

#include <string>
#include "io/CommandParser.hpp"
#include <controller/IController.hpp>

class ThemeController : public IController {
public:
    ThemeController() = default;
    ~ThemeController() = default;

    std::string getKeyword() const override;
    void execute(io::CommandHandle& cmd) override;
private:
};

#endif // THEME_CONTROLLER

