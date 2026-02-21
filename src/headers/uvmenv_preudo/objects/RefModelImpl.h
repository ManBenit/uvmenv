#ifndef REF_MODEL_IMPL_H
#define REF_MODEL_IMPL_H

#include "Factory.h"
using namespace std;

class RefModelImpl : public UVMObject {
public:
    void printInfo() override {
        cout << "[RefModelImpl] " << name << endl;
    }
};


#endif // REF_MODEL_IMPL_H

