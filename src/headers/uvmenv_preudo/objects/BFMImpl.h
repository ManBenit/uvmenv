#ifndef BFM_IMPL_H
#define BFM_IMPL_H

#include "../FactoryRegister.h"
#include "../UVMObject.h"
using namespace std;


class BFMImpl : public UVMObject {
public:
    virtual ~BFMImpl() = default;
    void printInfo() override;
    void copyBasefile() override;

private:
    // auto registration
    static ObjectRegister<BFMImpl> reg;
};


#endif // BFM_IMPL_H


