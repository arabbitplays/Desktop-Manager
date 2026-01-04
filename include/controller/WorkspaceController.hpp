#ifndef WORKSPACE_CONTROLLER
#define WORKSPACE_CONTROLLER

#include "controller/IController.hpp"
#include <cstdint>
class WorkspaceController : public IController {
public:
    WorkspaceController();
    ~WorkspaceController() = default;

    std::string getKeyword() const override;
    void execute(io::CommandHandle &cmd) override;

private:
    static constexpr char* HYPR_CTL = "/run/current-system/sw/bin/hyprctl";
    static constexpr char* JQ = "/run/current-system/sw/bin/jq";
    
    struct Workspace {
        uint32_t physical_id;
        uint32_t virtual_id;
    };

    void switchWorkspace(uint32_t target_virtual) const;
    void sendWindow(uint32_t target_virtual) const;
    void moveWindow(int32_t physical_delta) const;

    Workspace getCurrentWorkspace() const;
    std::string getActiveWindowId() const;

    std::vector<std::string> monitor_names;
};

#endif // WORKSPACE_CONTROLLER

