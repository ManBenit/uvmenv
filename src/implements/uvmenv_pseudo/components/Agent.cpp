#include "../../../headers/uvmenv_pseudo/components/Agent.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <regex>
#include <fstream>
#include <cmath>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


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

    ifstream agentBaseFile(agentBasePath);
    stringstream agentBuffer;
    agentBuffer << agentBaseFile.rdbuf();
    string agentContent = agentBuffer.str();
    agentContent = regex_replace(agentContent, regex("CLASS_NAME"), name );
    ofstream agetFile(joinStr({
        destPath, "__init__.py"
    }, PATH_SEP));
    agetFile << agentContent;


    filesystem::copy(
        monitorBasePath,
        destPath + PATH_SEP + "Monitor.py"
    );

    filesystem::copy(
        driverBasePath,
        destPath + PATH_SEP + "Driver.py"
    );

    ifstream baseFile(coverageBasePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
    vector<string> coverPoints;
    
    json config = readFileJson(joinStr({
        PROJECT_DIR, "config.json"
    }, PATH_SEP));
    string topModule = config["dut_design"]["top_module"];
    string topModuleLower = toLowerCase(topModule);

    string coverPLine;
    for(const auto& [module, signalProps] : dutSignals){
        if(module == topModule){
            for (const auto& signal : signalProps){
                coverPLine = "";
                coverPLine += doTabs(1) + "@CoverPoint('" + topModuleLower + "." + signal.name + "',\n";
                coverPLine += doTabs(2) + "xf=lambda tr: tr." + signal.name + ",\n";
                coverPLine += doTabs(2) + "bins = [\n";
                coverPLine += doTabs(3) + "i for i in range(" + to_string(2*signal.size) + ")\n";
                coverPLine += doTabs(2) + "]\n";
                coverPLine += doTabs(1) + ")";

                coverPoints.push_back(coverPLine);
            }   
        }
    }
    
    content = regex_replace(content, regex("COVER_POINTS"), joinStr(coverPoints, "\n") );

    // Write project file
    ofstream testFile(joinStr({
        destPath, "Coverage.py"
    }, PATH_SEP));
    testFile << content;
}

void Agent::create(){
    print("Create agent component");
}


// private
ComponentRegister<Agent> Agent::reg("Agent");


