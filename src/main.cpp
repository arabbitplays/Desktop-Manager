#include "DesktopManager.hpp"
#include "io/CommandParser.hpp"

int main(int argc, char* argv[]) {
    DesktopManager app;

    if (argc == 2 && std::string(argv[1]) == "--dev") {
        app.activateDevMode();
    } 

    app.init();
    app.run();
}
