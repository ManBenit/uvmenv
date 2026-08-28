#include "../../../include/uvmenv_handling/component_handling/list_component.h"

#include <string>
#include <filesystem>
#include <vector>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "../../../include/functions/utils.h"
#include "../../../include/functions/constants.h"
#include "../../../include/uvmenv_handling/general_handling/framework.h"
#include "../../../include/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../include/uvmenv_handling/component_handling/ptree_handling.h"
using namespace std;


// Require only name
vector<string> listBFMInterfaces (){
    return treeListInterface();
}

vector<string> listTests(){
    return treeListTest();
}


// Require Test
vector<string> listSequences  (const string& testName){
    return treeListSequences(testName);
}

vector<string> listSeqitems   (const string& testName){
    return treeListSeqitem(testName);
}


vector<string> listEnvsOnTest (const string& testName){
    return treeListEnvironments(testName);
}


// Require Test and Environment
// vector<string> listEnvsOnEnv (const string& testName, const string& envParentName){
//     return treeListEnvironments(testName);
// }


vector<string> listRefModels  (const string& testName, const string& envName){
    return treeListRefmodel(testName, envName);
}

vector<string> listAgents     (const string& testName, const string& envName){
    return treeListAgents(testName, envName);
}

vector<string> listScoreboards(const string& testName, const string& envName){
    return treeListScoreboards(testName, envName);
}


// UVMEnv characteristics
vector<string> listMiscelaneous(const string& testName){
    vector<string> existingMisces;
    const string miscDir = joinStr({
        TBENCH_DIR, testName, "Misces"
    }, PATH_SEP);

    for(const string& s: getFileNamesInDirectory(miscDir))
        existingMisces.push_back( splitString(s, '.')[0] );
        
    return existingMisces;
}

unordered_map<string, vector<Signal>> listRtlSignals(){
    return getDUTSignals('n');
}

unordered_map<string, vector<Signal>> refreshRtlSignals(){
    return getDUTSignals('r');
}

vector<string> listRtlModules(){
    // TODO: highlight top module
    vector<string> existingModules;
    const string& rtlModuleNames = trim( execCmdReturn(getScript("sys_commands") + "getRTLModuleNames " + DUT_HDL_DIR) );

    for(const string& mod: splitString(rtlModuleNames, ' ')){
        existingModules.push_back( splitString(mod, '.')[0] );
    }

    return existingModules;
}




