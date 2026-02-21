#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Factory.h"
#include "Agent.h"
#include "Scoreboard.h"
using namespace std;

class Environment : public UVMComponent {
private:
    vector<Agent*> agents;
    Scoreboard *scoreboard;

public:
    void printInfo() override {
        cout << "[Environment] " << name << ", Parent: " << parent << endl;
    }

    void addAgent(Agent* a) { agents.push_back(a); }
    void setScoreboard(Scoreboard* s) { scoreboard = s; }
    vector<Agent*> getAgents() { return agents; }
    Scoreboard* getScoreboard() { return scoreboard; }
};


#endif // ENVIRONMENT_H

