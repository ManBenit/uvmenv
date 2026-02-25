#include "../../../headers/uvmenv_preudo/components/Environment.h"


void Environment::addAgent(Agent* a) {
    agents.push_back(a);
}

void Environment::setScoreboard(Scoreboard* s) {
    scoreboard = s;
}

vector<Agent*> Environment::getAgents() {
    return agents;
}

Scoreboard* Environment::getScoreboard() {
    return scoreboard;
}



// @Override
void Environment::printInfo() {
    cout << "[Environment] " << name << ", Parent: " << parent << endl;
}


