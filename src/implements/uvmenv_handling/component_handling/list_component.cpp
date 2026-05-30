#include "../../../headers/uvmenv_handling/component_handling/list_component.h"

#include <string>
#include <filesystem>
#include <vector>
#include <vector>
#include <iostream>

#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
#include "../../../headers/uvmenv_handling/component_handling/ptree_handling.h"
using namespace std;

//vector<string> options = {"test", "env", "agent", "seqitem", "seqce", "scorebd", "refmod", "bfm"};
//string ptree_file = PROJECT_DIR + PATH_SEP + "ptree.yml";


// Require only name
std::vector<std::string> listBFMInterfaces (){
    return treeListInterface();
}

std::vector<std::string> listTests(){
    return treeListTest();
}


// Require Test
std::vector<std::string> listSequences         (const string& testName){
    return treeListSequences(testName);
}

std::vector<std::string> listSeqitems          (const string& testName){
    return treeListSeqitem(testName);
}


std::vector<std::string> listEnvsOnTest(const string& testName){
    return treeListEnvironments(testName);
}


// Require Test and Environment
// std::vector<std::string> listEnvsOnEnv (const string& testName, const string& envParentName){
//     return treeListEnvironments(testName);
// }


std::vector<std::string> listRefModels  (const string& testName, const string& envName){
    return treeListRefmodel(testName, envName);
}

std::vector<std::string> listAgents     (const string& testName, const string& envName){
    return treeListAgents(testName, envName);
}

std::vector<std::string> listScoreboards(const string& testName, const string& envName){
    return treeListScoreboards(testName, envName);
}




