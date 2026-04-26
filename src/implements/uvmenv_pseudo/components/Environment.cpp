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

void Environment::setTestContainer(const string& testName){
    this->testName = testName;
}


// @Override
void Environment::copyBaseFile(){
    filesystem::copy(
        basefilePath, 
        TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Envmnt" + PATH_SEP + name + PATH_SEP + PYMODULE
    );
}


// private
ComponentRegister<Environment> Environment::reg("Environment");



