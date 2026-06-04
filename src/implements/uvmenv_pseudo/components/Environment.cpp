#include "../../../headers/uvmenv_pseudo/components/Environment.h"

#include "../../../headers/functions/utils.h"

#include <iostream>
#include <regex>
#include <fstream>
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
    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    // Write project file
    ofstream testFile(joinStr({TBENCH_DIR, testName, "Envmnt", name, PYMODULE}, PATH_SEP));
    testFile << content;
}


// private
ComponentRegister<Environment> Environment::reg("Environment");



