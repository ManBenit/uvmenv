#ifndef MONITOR_H
#define MONITOR_H

#include "../Factory.h"
using namespace std;


class Monitor : public UVMComponent {
public:
    void printInfo() override {
        cout << "[Monitor] " << name << ", Parent: " << parent << endl;
    }
};

#endif // MONITOR_H
