#include "include/DesktopManager.hpp"
#include "controller/ThemeController.hpp"
#include "io/CommandParser.hpp"
#include <memory>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>


void DesktopManager::init() {
    theme_controller = std::make_shared<ThemeController>();
}

void DesktopManager::run() {
    int server = socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/desktop_manager.sock");
    unlink(addr.sun_path);

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

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
            for (const auto& arg : cmd->args) {
                std::cout << "|" << arg << "|" << std::endl;
            }
            if (theme_controller->getKeyword() == cmd->keyword) {
                theme_controller->execute(cmd);
            }
        }
        close(client);
    }
}
