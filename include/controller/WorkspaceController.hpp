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
    void switchWorkspace(uint32_t target_virtual) const;

    std::vector<std::string> monitor_names;
};

#endif // WORKSPACE_CONTROLLER

