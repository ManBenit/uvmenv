#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "../Factory.h"
using namespace std;

class Sequence : public UVMObject {
public:
    void printInfo() override {
        cout << "[Sequence] " << name << endl;
    }
};

#endif // SEQUENCE_H


