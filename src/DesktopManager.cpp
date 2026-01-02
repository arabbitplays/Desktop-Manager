
#include "include/DesktopManager.hpp"
#include "controller/ThemeController.hpp"
#include "controller/WorkspaceController.hpp"
#include "io/CommandParser.hpp"
#include <memory>

#include <ostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <util/MonitorUtil.hpp>

void DesktopManager::init() {
    controllers.push_back(std::make_shared<ThemeController>());
    controllers.push_back(std::make_shared<WorkspaceController>());
}

void DesktopManager::run() {
    std::string socket_path = "/run/desktop-manager/desktop-manager.sock"; 

    int server = socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, socket_path.c_str()); 
    unlink(addr.sun_path);

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    std::cout << "Listening on socket " << socket_path << std::endl;

    io::CommandParser parser;

    MonitorUtil::getMonitorNamesForCurrSystem();
    while (true) {
        int client = accept(server, nullptr, nullptr);
        char buf[256];
        int n = read(client, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = 0;
            std::string cmd_string(buf);
            io::CommandHandle cmd = parser.parseCommand(cmd_string);
            std::cout << "Received command: " << cmd_string << "\n";

            for (const auto& controller : controllers) {
                if (controller->getKeyword() == cmd->keyword) {
                    try {
                        controller->execute(cmd);
                    } catch (const std::exception& e) {
                        std::cout << "Error while executing command: " << e.what() << std::endl;
                    }
                }
            }
        }
        close(client);
    }
}
