#ifndef AGENT_H
#define AGENT_H

#include "Factory.h"
#include "Driver.h"
#include "Monitor.h"
#include "Coverage.h"
using namespace std;

class Agent : public UVMComponent {
private:
    Driver *driver;
    Monitor *monitor;
    Coverage *coverage;

public:
    void printInfo() override {
        cout << "[Agent] " << name << ", Parent: " << parent << endl;
    }

    void setDriver(Driver* d) { driver = d; }
    void setMonitor(Monitor* m) { monitor = m; }
    void setCoverage(Coverage* c) { coverage = c; }
    Driver* getDriver() { return driver; }
    Monitor* getMonitor() { return monitor; }
    Coverage* getCoverage() { return coverage; }
};


#endif // AGENT_H

