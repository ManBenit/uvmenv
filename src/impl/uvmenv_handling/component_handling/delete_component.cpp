#include "../../../include/uvmenv_handling/component_handling/delete_component.h"

#include <string>
#include <filesystem>
#include <vector>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "../../../include/uvmenv_pseudo/components/Top.h"
#include "../../../include/uvmenv_pseudo/components/Test.h"
#include "../../../include/uvmenv_pseudo/components/Environment.h"
#include "../../../include/uvmenv_pseudo/objects/Sequence.h"
#include "../../../include/uvmenv_pseudo/objects/BFMImpl.h"
#include "../../../include/uvmenv_pseudo/objects/SequenceItem.h"
#include "../../../include/uvmenv_pseudo/objects/RefModelImpl.h"

#include "../../../include/functions/utils.h"
#include "../../../include/functions/constants.h"
#include "../../../include/uvmenv_handling/general_handling/framework.h"
// #include "../../../include/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../include/uvmenv_handling/component_handling/ptree_handling.h"
using namespace std;


// Require only name
void deleteBFMInterface (const string& name){
    BFMImpl* bfm = (BFMImpl*) Factory::instance().createObject("BFMImpl", name);
    bfm->deleteFile(name);

    treeDeleteInterface(name);
}

void deleteTest(const string& name){
    Test* test = (Test*) Factory::instance().createComponent("Test", name, &Top::instance());
    test->deleteFile(name);

    treeDeleteTest(name);
}


// Require Test
void deleteSequence  (const string& name, const string& testName){
    Sequence* sequence = (Sequence*) Factory::instance().createObject("Sequence", name);
    sequence->setTestContainer(testName);
    sequence->deleteFile(name);

    return treeDeleteSequences(name, testName);
}

void deleteSeqitem   (const string& name, const string& testName){
    SequenceItem* seqitem = (SequenceItem*) Factory::instance().createObject("SequenceItem", name);
    seqitem->setTestContainer(testName);
    seqitem->deleteFile(name);

    return treeDeleteSeqitem(name, testName);
}


void deleteEnvOnTest(const string& name, const string& testName){
    Environment* env    = (Environment*) Factory::instance().createComponent("Environment", name, nullptr);
    env->setTestContainer(testName);
    env->deleteFile(name);

    return treeDeleteEnvironment(name, testName);
}


// Require Test and Environment
void deleteEnvOnEnv (const string& name, const string& testName, const string& envParentName){
    print("Comming soon...");
}


void deleteRefModel  (const string& name, const string& testName, const string& envName){
    RefModelImpl* refmodel = (RefModelImpl*) Factory::instance().createObject("RefModelImpl", name);
    refmodel->setTestContainer(testName);
    refmodel->setEnvContainer(envName);
    refmodel->deleteFile(name);

    return treeDeleteRefmodel(name, testName, envName);
}

void deleteAgent     (const string& name, const string& testName, const string& envName){
    Agent* agent = (Agent*) Factory::instance().createComponent("Agent", name, nullptr);
    agent->setTestContainer(testName);
    agent->setEnvContainer(envName);
    agent->deleteFile(name);

    return treeDeleteAgent(name, testName, envName);
}

void deleteScoreboard(const string& name, const string& testName, const string& envName){
    Scoreboard* scoreboard = (Scoreboard*) Factory::instance().createComponent("Scoreboard", name, nullptr);
    scoreboard->setTestContainer(testName);
    scoreboard->setEnvContainer(envName);
    scoreboard->deleteFile(name);

    return treeDeleteScoreboard(name, testName, envName);
}


// UVMEnv characteristics
// void deleteMiscelaneous(const string& name, const string& testName){
//     void existingMisces;
//     const string miscDir = joinStr({
//         TBENCH_DIR, testName, "Misces"
//     }, PATH_SEP);

//     for(const string& s: getFileNamesInDirectory(miscDir))
//         existingMisces.push_back( splitString(s, '.')[0] );
        
//     return existingMisces;
// }




