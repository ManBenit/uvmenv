#ifndef COVERAGE_H
#define COVERAGE_H

#include "../FactoryRegister.h"
#include "../UVMComponent.h"
using namespace std;

class Coverage : public UVMComponent {
public:
    virtual ~Coverage() = default;
    void printInfo() override;

private:
    // auto registration
    static ComponentRegister<Coverage> reg;
};

#endif // COVERAGE_H

