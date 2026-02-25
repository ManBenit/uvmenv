#ifndef REF_MODEL_IMPL_H
#define REF_MODEL_IMPL_H

#include "../FactoryRegister.h"
#include "../UVMObject.h"
using namespace std;

class RefModelImpl : public UVMObject {
public:
    virtual ~RefModelImpl() = default;
    void printInfo() override;

private:
    // auto registration
    static ObjectRegister<RefModelImpl> reg;
};


#endif // REF_MODEL_IMPL_H

