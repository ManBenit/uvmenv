#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "../FactoryRegister.h"
#include "../UVMObject.h"
using namespace std;

class Sequence : public UVMObject {
public:
    virtual ~Sequence() = default;
    void printInfo() override;
    void copyBasefile() override;

private:
    // auto registration
    static ObjectRegister<Sequence> reg;
};

#endif // SEQUENCE_H


