#ifndef SEQUENCE_ITEM_H
#define SEQUENCE_ITEM_H

#include "../UVMObject.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class SequenceItem : public UVMObject {

public:
    SequenceItem(const std::string& typeName, const std::string& name): UVMObject(typeName, name){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "SeqItemBase.py";
        requestBasePath = BASES_COMPONENT_DIR + PATH_SEP + "SeqItemRequestBase.py";
        responseBasePath = BASES_COMPONENT_DIR + PATH_SEP + "SeqItemResponseBase.py";
        uvmenvProjectDir = TBENCH_DIR + PATH_SEP + "SeqItm"; //AddAliasForREquestAndResponse
    }
    virtual ~SequenceItem() = default;

    void copyBaseFile() override;

    void setName(const std::string& name);
    void setTestContainer(const std::string& testName);
private:
    // auto registration
    static ObjectRegister<SequenceItem> reg;
    std::string name;
    std::string testName;
    std::string requestBasePath;
    std::string responseBasePath;
};

#endif // SEQUENCE_ITEM_H

