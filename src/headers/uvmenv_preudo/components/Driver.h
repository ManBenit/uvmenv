#ifndef DRIVER_H
#define DRIVER_H

#include "../Factory.h"
using namespace std;

class Driver : public UVMComponent {
public:
    void printInfo() override {
        cout << "[Driver] " << name << ", Parent: " << parent << endl;
    }
};

#endif // DRIVER_H
