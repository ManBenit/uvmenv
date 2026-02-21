#ifndef BFM_IMPL_H
#define BFM_IMPL_H

#include "../Factory.h"
using namespace std;


class BFMImpl : public UVMObject {
public:
    void printInfo() override {
        cout << "[BFMImpl] " << name << endl;
    }
};


#endif // BFM_IMPL_H


