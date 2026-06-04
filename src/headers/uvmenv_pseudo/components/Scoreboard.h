#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../UVMComponent.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class Scoreboard : public UVMComponent {

public:
    Scoreboard(const std::string& typeName, const std::string& name, UVMComponent* parent): UVMComponent(typeName, name, parent){
        basefilePath = BASES_COMPONENT_DIR + PATH_SEP + "ScoreboardBase.py";
        uvmenvProjectDir = ENVIRONMENT_DIR + PATH_SEP + "Scorbd";
    }
    virtual ~Scoreboard() = default;

    void copyBaseFile() override;

    void setName(const std::string& name);
    void setTestContainer(const std::string& testName);
    void setEnvContainer(const std::string& envName);

private:
    // auto registration
    static ComponentRegister<Scoreboard> reg;
    std::string name;
    std::string testName;
    std::string envName;

};

#endif // SCOREBOARD_H

