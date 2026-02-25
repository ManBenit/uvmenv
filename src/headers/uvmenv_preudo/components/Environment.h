#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Agent.h"
#include "Scoreboard.h"
#include "../UVMComponent.h"
#include "../FactoryRegister.h"
#include "../../functions/constants.h"

class Environment : public UVMComponent {
private:
    vector<Agent*> agents;
    Scoreboard *scoreboard;

public:
    Environment(const std::string& typeName, const std::string& name, UVMComponent* parent): UVMComponent(typeName, name, parent){
        basefilePath = BASES_REPRESENT_DIR + PATH_SEP + "EnvironmentBase.py";
        uvmenvProjectDir = ENVIRONMENT_DIR;
    }
    virtual ~Environment() = default;

    void addAgent(Agent* a);
    void setScoreboard(Scoreboard* s);
    vector<Agent*> getAgents();
    Scoreboard* getScoreboard();

private:
    // auto registration
    static ComponentRegister<Environment> reg;
};


#endif // ENVIRONMENT_H

