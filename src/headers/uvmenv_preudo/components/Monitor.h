#ifndef MONITOR_H
#define MONITOR_H

#include "../FactoryRegister.h"
#include "../UVMComponent.h"
using namespace std;


class Monitor : public UVMComponent {
public:
    virtual ~Monitor() = default;
    void printInfo() override;

private:
    // auto registration
    static ComponentRegister<Monitor> reg;
};

#endif // MONITOR_H
