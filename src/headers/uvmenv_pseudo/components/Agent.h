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
        agentBasePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentBase.py";
        driverBasePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentDriverBase.py";
        monitorBasePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentMonitorBase.py";
        coverageBasePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentCoverageBase.py";
    }
    virtual ~Agent() = default;

    void setDriver(Driver* d);
    void setMonitor(Monitor* m);
    void setCoverage(Coverage* c);
    Driver* getDriver();
    Monitor* getMonitor();
    Coverage* getCoverage();

    void copyBaseFile() override;
    void create() override;

    void setName(const std::string& name);
    void setTestContainer(const std::string& testName);
    void setEnvContainer(const std::string& envName);
    void setAgentType(const std::string& agentType);

private:
    // auto registration
    static ComponentRegister<Agent> reg;
    std::string name;
    std::string testName;
    std::string envName;
    std::string agentType;

    std::string agentBasePath;
    std::string driverBasePath;
    std::string monitorBasePath;
    std::string coverageBasePath;
};


#endif // AGENT_H

