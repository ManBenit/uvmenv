#ifndef SEQUENCE_ITEM_H
#define SEQUENCE_ITEM_H

#include "../UVMObject.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class SequenceItem : public UVMObject {

public:
    SequenceItem(const std::string& typeName, const std::string& name): UVMObject(typeName, name){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "SeqItemBase.py";
        uvmenvProjectDir = TBENCH_DIR + PATH_SEP + "SeqItm"; //AddAliasForREquestAndResponse
    }
    virtual ~SequenceItem() = default;

private:
    // auto registration
    static ObjectRegister<SequenceItem> reg;
    
};

#endif // SEQUENCE_ITEM_H

