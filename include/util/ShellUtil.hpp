#ifndef SHELL_UTIL
#define SHELL_UTIL

#include <array>
#include <charconv>
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

    static void printShellOutput(const std::string& output) {
        std::cout << output << std::endl;
    }


    static int32_t parseStringToInt(const std::string& arg) {
        int32_t value;
        auto [ptr, ec] = std::from_chars(arg.data(), arg.data() + arg.size(), value);
        
        if (ec == std::errc{} && ptr == arg.data() + arg.size()) {
            return value;
        } else {
            throw std::runtime_error("Error while parsing string to int");
        }
    }
private:
};

#endif // SHELL_UTIL

