#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Environment.h"
using namespace std;


void Environment::addAgent(Agent* a) {
    agents.push_back(a);
}

void Environment::addScoreboard(Scoreboard* s) {
    scoreboards.push_back(s);
}

vector<Agent*> Environment::getAgents() {
    return agents;
}

vector<Scoreboard*> Environment::getScoreboards() {
    return scoreboards;
}

void Environment::setName(const string& name){
    this->name = name;
}


// @Override
void Environment::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Environment> Environment::reg("Environment");



