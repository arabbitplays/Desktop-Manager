#ifndef MONITOR_UTIL
#define MONITOR_UTIL

#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>

class MonitorUtil {
public:
    MonitorUtil() = default;
    ~MonitorUtil() = default;

    static std::vector<std::string> getMonitorNamesForCurrSystem() {
        std::string hostname = getHostname();
        if (hostname == "nix-desktop") {
            return { "HDMI-A-3", "DP-2", "HDMI-A-4" };
        }

        throw std::runtime_error("Hostname '" + hostname + "' not known!");
    }
private:
    static std::string getHostname() {
        char hostname[255];
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            return hostname;
        }
        return "";
    }
};

#endif // MONITOR_UTIL

