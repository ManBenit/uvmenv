#ifndef DRIVER_H
#define DRIVER_H

#include "../UVMComponent.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class Driver : public UVMComponent {

public:
    Driver(const std::string& typeName, const std::string& name, UVMComponent* parent): UVMComponent(typeName, name, parent){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentDriverBase.py";
        uvmenvProjectDir = ENVIRONMENT_DIR + PATH_SEP + "Agents"; //AddAlias
    }
    virtual ~Driver() = default;

    void copyBaseFile() override;

private:
    // auto registration
    static ComponentRegister<Driver> reg;

};

#endif // DRIVER_H
