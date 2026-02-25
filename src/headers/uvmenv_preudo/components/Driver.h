#ifndef DRIVER_H
#define DRIVER_H

#include "../FactoryRegister.h"
#include "../UVMComponent.h"
using namespace std;

class Driver : public UVMComponent {
public:
    virtual ~Driver() = default;
    void printInfo() override;
    void copyBasefile() override;

private:
    // auto registration
    static ComponentRegister<Driver> reg;
};

#endif // DRIVER_H
