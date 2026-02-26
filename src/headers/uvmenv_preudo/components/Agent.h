#ifndef AGENT_H
#define AGENT_H

#include "Driver.h"
#include "Monitor.h"
#include "Coverage.h"
#include "../UVMComponent.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class Agent : public UVMComponent {

private:
    Driver *driver;
    Monitor *monitor;
    Coverage *coverage;

public:
    Agent(const std::string& typeName, const std::string& name, UVMComponent* parent): UVMComponent(typeName, name, parent){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentBase.py";
        uvmenvProjectDir = ENVIRONMENT_DIR + PATH_SEP + "Agents";
    }
    virtual ~Agent() = default;

    void setDriver(Driver* d);
    void setMonitor(Monitor* m);
    void setCoverage(Coverage* c);
    Driver* getDriver();
    Monitor* getMonitor();
    Coverage* getCoverage();

    void copyBaseFile() override;

private:
    // auto registration
    static ComponentRegister<Agent> reg;
    
};


#endif // AGENT_H

