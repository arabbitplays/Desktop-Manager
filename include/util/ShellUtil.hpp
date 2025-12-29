#ifndef SHELL_UTIL
#define SHELL_UTIL

#include <array>
#include <cstdio>
#include <iostream>
#include <string>
class ShellUtil {
public:
    ShellUtil() = default;
    ~ShellUtil() = default;

    static std::string executeShellCommand(const std::string& cmd) {
        std::cout << "Executing shell command '" << cmd << "'" << std::endl;

        std::array<char, 255> buffer{};
        std::string result;

        FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe) {
            return "";
        }

        while (fgets(buffer.data(), buffer.size(), pipe)) {
            result += buffer.data();
        }

        pclose(pipe);

        if (!result.empty() && result.back() == '\n') {
            result.pop_back();
        }

        return result;
    }
private:
};

#endif // SHELL_UTIL

