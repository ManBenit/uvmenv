#include "../../../headers/uvmenv_pseudo/components/Agent.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
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
        coverageBasePath,
        destPath + PATH_SEP + "Coverage.py"
    );




    ifstream baseFile(driverBasePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
    vector<string> inputs;

    for(const auto& [signalName, signalProps] : dutSignals)
        for (const auto& signal : signalProps)
            if(signal.type == "INPUT")
                inputs.push_back(
                    doTabs(4) + signal.name + " = op." + signal.name
                );
    content = regex_replace(content, regex("BFM_SET"), joinStr(inputs, ",\n") );

    // Write project file
    ofstream testFile(joinStr({
        destPath, "Driver.py"
    }, PATH_SEP));
    testFile << content;
}

void Agent::create(){
    cout << "Create agent component" << endl;
}


// private
ComponentRegister<Agent> Agent::reg("Agent");


