#include "../../../headers/uvmenv_pseudo/components/Environment.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
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

void Environment::editFile(const string& name){
    const string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDir;

    if(!filesystem::exists(uvmenvProjectDir)){
        printError("Does not exist " + name);
        exit(5);
    }
    
    int sysResult = system(file.c_str());
    if (sysResult== 0) {
        printInfo("Finished edition of " + name);
    } else {
        printError( "Something went wrong while editing " + name + ". Returned code " + to_string(sysResult) );
    }
}


// @Override
void Environment::copyBaseFile(){
    uvmenvProjectDir = joinStr({TBENCH_DIR, testName, "Envmnt", name, PYMODULE}, PATH_SEP);


    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    // Write project file
    ofstream outFile(uvmenvProjectDir);
    outFile << content;
    outFile.close();
}


// private
ComponentRegister<Environment> Environment::reg("Environment");



