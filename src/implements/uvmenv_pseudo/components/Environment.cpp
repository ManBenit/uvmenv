#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Environment.h"
using namespace std;


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
void Environment::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Environment> Environment::reg("Environment");



