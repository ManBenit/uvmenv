#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "../UVMObject.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class Sequence : public UVMObject {

public:
    Sequence(const std::string& typeName, const std::string& name): UVMObject(typeName, name){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "SequenceBase.py";
        uvmenvProjectDir = TBENCH_DIR + PATH_SEP + "Seqnce";
    }
    virtual ~Sequence() = default;

    void copyBaseFile() override;

    void setName(const std::string& name);
    void setTestContainer(const std::string& testName);
private:
    // auto registration
    static ObjectRegister<Sequence> reg;
    std::string name;
    std::string testName;
};

#endif // SEQUENCE_H


