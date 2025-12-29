#ifndef ICONTROLLER
#define ICONTROLLER

#include "io/CommandParser.hpp"

class IController {
public:
    IController() = default;
    ~IController() = default;

    virtual void execute(io::CommandHandle& cmd) = 0;
    virtual std::string getKeyword() const = 0;
private:
};

#endif // ICONTROLLER

