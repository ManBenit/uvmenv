#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Agent.h"
#include "Scoreboard.h"
#include "../FactoryRegister.h"
#include "../UVMComponent.h"
using namespace std;

class Environment : public UVMComponent {
private:
    vector<Agent*> agents;
    Scoreboard *scoreboard;

public:
    virtual ~Environment() = default;
    void addAgent(Agent* a);
    void setScoreboard(Scoreboard* s);
    vector<Agent*> getAgents();
    Scoreboard* getScoreboard();


    void printInfo() override;

private:
    // auto registration
    static ComponentRegister<Environment> reg;
};


#endif // ENVIRONMENT_H

