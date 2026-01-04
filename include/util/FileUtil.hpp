#ifndef FILE_UTIL
#define FILE_UTIL

#include "util/ShellUtil.hpp"
#include <fstream>

class FileUtil {
public:
    FileUtil() = default;
    ~FileUtil() = default;

    static void copyFile(const std::string& src_path, const std::string& dst_path) {
        ShellUtil::executeShellCommand("cp " + src_path + " " + dst_path);
    }

    static void overwriteFile(const std::string& path, const std::string& content) {
        std::ofstream file(path, std::ios::out | std::ios::trunc);
        if (!file) {
            throw std::runtime_error("Failed to open file: " + path);
        }

        file << content;
        file.close();
    }
private:
};

#endif // FILE_UTIL

