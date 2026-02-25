#ifndef AGENT_H
#define AGENT_H

#include "Driver.h"
#include "Monitor.h"
#include "Coverage.h"
#include "../UVMComponent.h"
#include "../FactoryRegister.h"
using namespace std;

class Agent : public UVMComponent {
private:
    Driver *driver;
    Monitor *monitor;
    Coverage *coverage;

public:
    virtual ~Agent() = default;

    void setDriver(Driver* d);
    void setMonitor(Monitor* m);
    void setCoverage(Coverage* c);
    Driver* getDriver();
    Monitor* getMonitor();
    Coverage* getCoverage();


    void printInfo() override;
    
private:
    // auto registration
    static ComponentRegister<Agent> reg;
};


#endif // AGENT_H

