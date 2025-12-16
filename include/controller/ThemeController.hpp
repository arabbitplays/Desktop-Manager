#ifndef THEME_CONTROLLER
#define THEME_CONTROLLER

#include <string>
#include "io/CommandParser.hpp"

class ThemeController {
public:
    ThemeController() = default;
    ~ThemeController() = default;

    std::string getKeyword() const;
    void execute(io::CommandHandle& cmd);
private:
};

#endif // THEME_CONTROLLER

