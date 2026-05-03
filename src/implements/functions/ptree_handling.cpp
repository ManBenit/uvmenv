#include "../../headers/functions/ptree_handling.h"
#include "../../headers/functions/utils.h"
#include "../../headers/functions/constants.h"
#include <string>
#include <vector>
#include <iostream> ///
#include <yaml-cpp/yaml.h>
using namespace std;


const string ptreeFilePath = PROJECT_DIR + PATH_SEP + ".ptree.yml";

// ==================
// BFM INTERFACE
// ==================
void treeAddInterface(const string& name){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["itfaces"].push_back(name);
    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListInterface(){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> interfaceNames;

    for (const auto& itface : treeFile["top"]["itfaces"])
        interfaceNames.push_back(itface.as<string>());

    return interfaceNames;
}

void treeDeleteInterface(const string& name){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    YAML::Node newItfaces;

    for (const auto& itface : treeFile["top"]["itfaces"])
        if(itface.as<string>() != name)
            newItfaces.push_back(itface);

    treeFile["top"]["itfaces"] = newItfaces;
    writeFileYaml(ptreeFilePath, treeFile);
}


// ==================
// TEST
// ==================
void treeAddTest(const string& name){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    
    treeFile["top"]["tests"][name] = YAML::Null;
    treeFile["top"]["tests"][name]["seqitems"] = YAML::Null;
    treeFile["top"]["tests"][name]["sequences"] = YAML::Null;
    treeFile["top"]["tests"][name]["envs"] = YAML::Null;

    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListTest(){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> testNames;

    for (const auto& test : treeFile["top"]["tests"])
        testNames.push_back(test.first.as<string>());

    return testNames;
}

void treeDeleteTest(const string& name){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["tests"].remove(name);

    if( treeFile["top"]["tests"].size() == 0)
        treeFile["top"]["tests"] = YAML::Null;

    writeFileYaml(ptreeFilePath, treeFile);
}


// ==================
// SEQUENCE ITEM
// ==================
void treeAddSeqitem(const string& name, const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["tests"][testName]["seqitems"].push_back(name);
    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListSeqitem(const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> seqItemNames;

    for (const auto& seqitem : treeFile["top"]["tests"][testName]["seqitems"])
        seqItemNames.push_back(seqitem.as<string>());

    return seqItemNames;
}

void treeDeleteSeqitem(const string& name, const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    YAML::Node newSeqitems;

    for (const auto& seqitem : treeFile["top"]["tests"][testName]["seqitems"])
        if(seqitem.as<string>() != name)
            newSeqitems.push_back(seqitem);

    treeFile["top"]["tests"][testName]["seqitems"] = newSeqitems;
    writeFileYaml(ptreeFilePath, treeFile);
}



// ==================
// SEQUENCES
// ==================
void treeAddSequences(const string& name, const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["tests"][testName]["sequences"].push_back(name);
    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListSequences(const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> seqItemNames;

    for (const auto& seqitem : treeFile["top"]["tests"][testName]["sequences"])
        seqItemNames.push_back(seqitem.as<string>());

    return seqItemNames;
}

void treeDeleteSequences(const string& name, const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    YAML::Node newSeqitems;

    for (const auto& seqitem : treeFile["top"]["tests"][testName]["sequences"])
        if(seqitem.as<string>() != name)
            newSeqitems.push_back(seqitem);

    treeFile["top"]["tests"][testName]["sequences"] = newSeqitems;
    writeFileYaml(ptreeFilePath, treeFile);
}


// ==================
// ENVIRONMENT
// ==================
void treeAddEnvironment(const string& name, const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    
    treeFile["top"]["tests"][testName]["envs"][name] = YAML::Null;
    treeFile["top"]["tests"][testName]["envs"][name]["refmodels"] = YAML::Null;
    treeFile["top"]["tests"][testName]["envs"][name]["agents"] = YAML::Null;
    treeFile["top"]["tests"][testName]["envs"][name]["scoreboards"] = YAML::Null;

    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListEnvironments(const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> envNames;
    for (const auto& env : treeFile["top"]["tests"][testName]["envs"])
        envNames.push_back(env.first.as<string>());

    return envNames;
}

void treeDeleteEnvironment(const string& name, const string& testName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["tests"][testName]["envs"].remove(name);

    if( treeFile["top"]["tests"][testName]["envs"].size() == 0)
        treeFile["top"]["tests"][testName]["envs"] = YAML::Null;

    writeFileYaml(ptreeFilePath, treeFile);
}




// ==================
// REFMODEL
// ==================
void treeAddRefmodel(const string& name, const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["tests"][testName]["envs"][envName]["refmodels"].push_back(name);
    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListRefmodel(const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> seqItemNames;

    for (const auto& seqitem : treeFile["top"]["tests"][testName]["envs"][envName]["refmodels"])
        seqItemNames.push_back(seqitem.as<string>());

    return seqItemNames;
}

void treeDeleteRefmodel(const string& name, const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    YAML::Node newRefmodels;

    for (const auto& refmodel : treeFile["top"]["tests"][testName]["envs"][envName]["refmodels"])
        if(refmodel.as<string>() != name)
            newRefmodels.push_back(refmodel);

    treeFile["top"]["tests"][testName]["envs"][envName]["refmodels"] = newRefmodels;
    writeFileYaml(ptreeFilePath, treeFile);
}


// ==================
// AGENTS
// ==================
void treeAddAgent(const string& name, const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["tests"][testName]["envs"][envName]["agents"].push_back(name);
    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListAgents(const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> agents;

    for (const auto& agent : treeFile["top"]["tests"][testName]["envs"][envName]["agents"])
        agents.push_back(agent.as<string>());

    return agents;
}

void treeDeleteAgent(const string& name, const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    YAML::Node newAgent;

    for (const auto& agent : treeFile["top"]["tests"][testName]["envs"][envName]["agents"])
        if(agent.as<string>() != name)
            newAgent.push_back(agent);

    treeFile["top"]["tests"][testName]["envs"][envName]["agents"] = newAgent;
    writeFileYaml(ptreeFilePath, treeFile);
}


// ==================
// SCOREBOARD
// ==================
void treeAddScoreboard(const string& name, const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    treeFile["top"]["tests"][testName]["envs"][envName]["scoreboards"].push_back(name);
    writeFileYaml(ptreeFilePath, treeFile);
}

vector<string> treeListScoreboards(const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    vector<string> seqItemNames;

    for (const auto& seqitem : treeFile["top"]["tests"][testName]["envs"][envName]["scoreboards"])
        seqItemNames.push_back(seqitem.as<string>());

    return seqItemNames;
}

void treeDeleteScoreboard(const string& name, const string& testName, const string& envName){
    YAML::Node treeFile = readFileYaml(ptreeFilePath);
    YAML::Node newScoreboard;

    for (const auto& scoreboard : treeFile["top"]["tests"][testName]["envs"][envName]["scoreboards"])
        if(scoreboard.as<string>() != name)
            newScoreboard.push_back(scoreboard);

    treeFile["top"]["tests"][testName]["envs"][envName]["scoreboards"] = newScoreboard;
    writeFileYaml(ptreeFilePath, treeFile);
}

