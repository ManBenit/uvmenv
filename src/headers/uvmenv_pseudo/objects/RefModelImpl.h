#ifndef REF_MODEL_IMPL_H
#define REF_MODEL_IMPL_H

#include "../UVMObject.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class RefModelImpl : public UVMObject {
    
public:
    RefModelImpl(const std::string& typeName, const std::string& name): UVMObject(typeName, name){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "RefmodelImplBase.py";
    }
    virtual ~RefModelImpl() = default;

    void copyBaseFile() override;


    void editFile(const std::string& name);
    void deleteFile(const std::string& name);
    void setName(const std::string& name);
    void setTestContainer(const std::string& testName);
    void setEnvContainer(const std::string& envName);

private:
    // auto registration
    static ObjectRegister<RefModelImpl> reg;
    std::string name;
    std::string testName;
    std::string envName;
};


#endif // REF_MODEL_IMPL_H

