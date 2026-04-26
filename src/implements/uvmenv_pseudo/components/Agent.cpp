#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Agent.h"
using namespace std;


void Agent::setDriver(Driver* d) { 
    driver = d; 
}

void Agent::setMonitor(Monitor* m) { 
    monitor = m; 
}

void Agent::setCoverage(Coverage* c) { 
    coverage = c; 
}

Driver* Agent::getDriver() { 
    return driver; 
}
Monitor* Agent::getMonitor() { 
    return monitor; 
}

Coverage* Agent::getCoverage() { 
    return coverage; 
}

void Agent::setName(const string& name){
    this->name = name;
}

void Agent::setTestContainer(const string& testName){
    this->testName = testName;
}

void Agent::setEnvContainer(const string& envName){
    this->envName = envName;
}



// @Override
void Agent::copyBaseFile(){
    string destPath = TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Envmnt" + PATH_SEP + envName + PATH_SEP + "Agents" + PATH_SEP + name;

    filesystem::create_directory(destPath);

    filesystem::copy(
        agentBasePath,
        destPath + PATH_SEP + "__init__.py"
    );

    filesystem::copy(
        monitorBasePath,
        destPath + PATH_SEP + "Monitor.py"
    );

    filesystem::copy(
        driverBasePath,
        destPath + PATH_SEP + "Driver.py"
    );

    filesystem::copy(
        coverageBasePath,
        destPath + PATH_SEP + "Coverage.py"
    );
}

void Agent::create(){
    cout << "Create agent component" << endl;
}


// private
ComponentRegister<Agent> Agent::reg("Agent");


