#include "DesktopManager.hpp"
#include "io/CommandParser.hpp"

int main(int argc, char* argv[]) {
    DesktopManager app;

    if (argc == 1 && std::string(argv[0]) == "--dev") {
        app.activateDevMode();
    } 

    app.init();
    app.run();
}
