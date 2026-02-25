#ifndef SEQUENCE_ITEM_H
#define SEQUENCE_ITEM_H

#include "../FactoryRegister.h"
#include "../UVMObject.h"
using namespace std;

class SequenceItem : public UVMObject {
public:
    virtual ~SequenceItem() = default;
    void printInfo() override;

private:
    // auto registration
    static ObjectRegister<SequenceItem> reg;
};

#endif // SEQUENCE_ITEM_H

