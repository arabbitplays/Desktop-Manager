#ifndef FILE_UTIL
#define FILE_UTIL

#include "util/ShellUtil.hpp"
class FileUtil {
public:
    FileUtil() = default;
    ~FileUtil() = default;

    static void copyFile(std::string& src_path, std::string& dst_path) {
        ShellUtil::executeShellCommand("cp " + src_path + " " + dst_path);
    }
private:
};

#endif // FILE_UTIL

