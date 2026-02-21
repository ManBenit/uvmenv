#ifndef COVERAGE_H
#define COVERAGE_H

#include "../Factory.h"
using namespace std;

class Coverage : public UVMComponent {
public:
    void printInfo() override {
        cout << "[Coverage] " << name << ", Parent: " << parent << endl;
    }
};

#endif // COVERAGE_H

