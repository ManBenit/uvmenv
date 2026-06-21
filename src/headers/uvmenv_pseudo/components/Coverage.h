#ifndef COVERAGE_H
#define COVERAGE_H

#include "../UVMComponent.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class Coverage : public UVMComponent {

public:
    Coverage(const std::string& typeName, const std::string& name, UVMComponent* parent): UVMComponent(typeName, name, parent){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "AgentCoverageBase.py";
        uvmenvProjectDir = ENVIRONMENT_DIR + PATH_SEP + "Agents"; //AddAlias
    }
    virtual ~Coverage() = default;

    void copyBaseFile() override;

private:
    // auto registration
    static ComponentRegister<Coverage> reg;
    
};

#endif // COVERAGE_H

