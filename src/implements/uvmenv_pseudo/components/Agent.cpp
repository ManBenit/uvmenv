#include "../../../headers/uvmenv_pseudo/components/Agent.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/pconfig_handling.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <regex>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <yaml-cpp/yaml.h>
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

void Agent::setAgentType(const string& agentType){
    this->agentType = agentType;
}

void Agent::editFile(const string& name, const string& element){
    uvmenvProjectDir = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "Agents", name
    }, PATH_SEP);
    int sysResult = 0;
    string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDir;

    if(!filesystem::exists(uvmenvProjectDir)){
        printError("[Agent] Does not exist " + name);
        exit(5);
    }

    if(element == "")
        file += PATH_SEP + PYMODULE;
    else if(element == "drv")
        file += PATH_SEP + "Driver.py";
    else if(element == "mon")
        file += PATH_SEP + "Monitor.py";
    else if(element == "cov")
        file += PATH_SEP + "Coverage.py";
    else{
        printError("Wrong element of Agent " + name);
        exit(5);
    }
    
    sysResult = system(file.c_str());
    if (sysResult== 0) {
        printInfo("Finished edition of " + name);
    } else {
        printError( "Something went wrong while editing " + name + ". Returned code " + to_string(sysResult) );
    }
}

void Agent::deleteFile(const string& name){
    const string toDelete = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "Agents", name
    }, PATH_SEP);
    
    if(!filesystem::exists(toDelete)){
        printError("[Agent] Does not exist " + name);
        exit(5);
    }
    
    filesystem::remove_all(toDelete);
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
        printError("Missing agent type for creation: --type < std | psv | act | rct >");
        exit(5);
    }


    uvmenvProjectDir = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "Agents", name
    }, PATH_SEP);


    filesystem::create_directory(uvmenvProjectDir);


    ifstream agentBaseFile(agentBasePath);
    stringstream agentBuffer;
    agentBuffer << agentBaseFile.rdbuf();
    string agentContent = agentBuffer.str();
    agentContent = regex_replace(agentContent, regex("CLASS_NAME"), name );
    ofstream agentFile(joinStr({
        uvmenvProjectDir, PYMODULE
    }, PATH_SEP));
    agentFile << agentContent;
    agentFile.close();



    if(copyMonitor){
        filesystem::copy(
            monitorBasePath,
            uvmenvProjectDir + PATH_SEP + "Monitor.py"
        );
    }

    if(copyDriver){
        filesystem::copy(
            driverBasePath,
            uvmenvProjectDir + PATH_SEP + "Driver.py"
        );
    }

    if(copyCoverage){
        ifstream baseFile(coverageBasePath);
        stringstream buffer;
        buffer << baseFile.rdbuf();
        string content = buffer.str();

        unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
        vector<string> coverPoints;
        
        string topModule = getProjectDutDesign(PROJECT_DIR, "top_module");
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
            uvmenvProjectDir, "Coverage.py"
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


