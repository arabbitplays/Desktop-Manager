#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

int main() {
    int server = socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/desktop_manager.sock");
    unlink(addr.sun_path);

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    while (true) {
        int client = accept(server, nullptr, nullptr);
        char buf[256];
        int n = read(client, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = 0;
            std::string cmd(buf);
            std::cout << "Received command: " << cmd << "\n";
            // handle command...
        }
        close(client);
    }
}
