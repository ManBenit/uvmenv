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

void Agent::setAgentType(const string& agentType){
    this->agentType = agentType;
}



// @Override
void Agent::copyBaseFile(){
    // TODO: Add type identifier to be able to print the agent type when listing
    /**
     *                  drv  mon  cov
        standard (std)   1    1    1
        passive  (psv)   0    1    1
        active   (act)   1    0    0
        reactive (rct)   1    1    1
     */
    bool copyMonitor = false;
    bool copyDriver = false;
    bool copyCoverage = false;

    copyDriver   = agentType=="std" || agentType=="act" || agentType=="rct";
    copyMonitor  = agentType=="std" || agentType=="psv" || agentType=="rct";
    copyCoverage = agentType=="std" || agentType=="psv" || agentType=="rct";

    if(!copyMonitor && !copyDriver && !copyCoverage){
        printError("Missing agent type for creation: std | psv | act | rct");
        exit(5);
    }


    
    string destPath = TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Envmnt" + PATH_SEP + envName + PATH_SEP + "Agents" + PATH_SEP + name;

    filesystem::create_directory(destPath);

    ifstream agentBaseFile(agentBasePath);
    stringstream agentBuffer;
    agentBuffer << agentBaseFile.rdbuf();
    string agentContent = agentBuffer.str();
    agentContent = regex_replace(agentContent, regex("CLASS_NAME"), name );
    ofstream agentFile(joinStr({
        destPath, "__init__.py"
    }, PATH_SEP));
    agentFile << agentContent;
    agentFile.close();



    if(copyMonitor){
        filesystem::copy(
            monitorBasePath,
            destPath + PATH_SEP + "Monitor.py"
        );
    }

    if(copyDriver){
        filesystem::copy(
            driverBasePath,
            destPath + PATH_SEP + "Driver.py"
        );
    }

    if(copyCoverage){
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
        ofstream covFile(joinStr({
            destPath, "Coverage.py"
        }, PATH_SEP));
        covFile << content;
        covFile.close();
    }
}

void Agent::create(){
    print("Create agent component");
}


// private
ComponentRegister<Agent> Agent::reg("Agent");


