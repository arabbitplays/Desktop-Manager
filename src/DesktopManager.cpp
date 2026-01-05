
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
    std::string socket_path = dev_mode_active
        ? "/tmp/desktop-manager-dev.sock"
        : std::string(getenv("XDG_RUNTIME_DIR")) + "/desktop-manager/desktop-manager.sock"; 

    int server = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server < 0) { perror("socket"); exit(1); }

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, socket_path.c_str()); 
    unlink(addr.sun_path);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) < 0) { 
        perror("bind");
        exit(1);
    }

    if (listen(server, 5) < 0) {
        perror("listen");
        exit(1);
    }

    std::cout << "Listening on socket " << socket_path << std::endl;

    io::CommandParser parser;

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
                    std::string response = "";
                    try {
                        response = controller->execute(cmd);
                    } catch (const std::exception& e) {
                        response = "Error while executing command: " + std::string(e.what());
                        
                    }
                    write(client, response.c_str(), response.size());
                    std::cout << "Respnse:\n" << response << std::endl;
                }
            }

            std::string separator(100, '-');
            std::cout << separator << "\n";
        }
        close(client);
    }
}

void DesktopManager::activateDevMode() {
    dev_mode_active = true;
}
