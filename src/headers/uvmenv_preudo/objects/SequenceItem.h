#ifndef SEQUENCE_ITEM_H
#define SEQUENCE_ITEM_H

#include "Factory.h"
using namespace std;

class SequenceItem : public UVMObject {
public:
    void printInfo() override {
        cout << "[SequenceItem] " << name << endl;
    }
};

#endif // SEQUENCE_ITEM_H

