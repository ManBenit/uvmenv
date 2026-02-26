#ifndef REF_MODEL_IMPL_H
#define REF_MODEL_IMPL_H

#include "../UVMObject.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class RefModelImpl : public UVMObject {
    
public:
    RefModelImpl(const std::string& typeName, const std::string& name): UVMObject(typeName, name){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "RefmodelImplBase.py";
        uvmenvProjectDir = REFMODEL_DIR + PATH_SEP + "_impl";
    }
    virtual ~RefModelImpl() = default;

    void copyBaseFile() override;

private:
    // auto registration
    static ObjectRegister<RefModelImpl> reg;

};


#endif // REF_MODEL_IMPL_H

