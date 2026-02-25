#ifndef MONITOR_H
#define MONITOR_H

#include "../UVMComponent.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class Monitor : public UVMComponent {

public:
    Monitor(const std::string& typeName, const std::string& name, UVMComponent* parent): UVMComponent(typeName, name, parent){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentMonitorBase.py";
        uvmenvProjectDir = ENVIRONMENT_DIR + PATH_SEP + "Agents"; //AddAlias
    }
    virtual ~Monitor() = default;

private:
    // auto registration
    static ComponentRegister<Monitor> reg;

};

#endif // MONITOR_H
