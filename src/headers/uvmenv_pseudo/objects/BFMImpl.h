#ifndef BFM_IMPL_H
#define BFM_IMPL_H

#include "../UVMObject.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class BFMImpl : public UVMObject {

public:
    BFMImpl(const std::string& typeName, const std::string& name): UVMObject(typeName, name){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "BFMImplBase.py";
        uvmenvProjectDir = BFM_DIR + PATH_SEP + "_impl";
    }
    virtual ~BFMImpl() = default;

    void copyBaseFile() override;

    void setName(const std::string& name);

private:
    // auto registration
    static ObjectRegister<BFMImpl> reg;
    std::string name;

};


#endif // BFM_IMPL_H


