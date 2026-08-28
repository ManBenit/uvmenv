#include "../../../include/uvmenv_handling/component_handling/ptree_handling.h"
#include "../../../include/functions/utils.h"
#include "../../../include/functions/constants.h"
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
using namespace std;

const string configFilePath = PATH_SEP + "config.yml";



// ==================
// 
// ==================

string getProjectId(const string& currProj){
    YAML::Node configFile = readFileYaml(currProj + configFilePath);
    return trim( configFile["id"].as<string>() );
}

string getProjectName(const string& currProj){
    YAML::Node configFile = readFileYaml(currProj + configFilePath);
    return configFile["name"].as<string>();
}

string getProjectSimulation(const string& currProj, string field){
    YAML::Node configFile = readFileYaml(currProj + configFilePath);
    return configFile["simulation"][field].as<string>();
}

string getProjectDutDesign(const string& currProj, string field){
    YAML::Node configFile = readFileYaml(currProj + configFilePath);
    return configFile["dut_design"][field].as<string>();
}

string getProjectDutCs4Seq(const string& currProj, string field){
    YAML::Node configFile = readFileYaml(currProj + configFilePath);
    return configFile["dut_cs4_seq"][field].as<string>();
}

// Possibly will not be used
string getProjectUvmComponents(const string& currProj, string field){
    YAML::Node configFile = readFileYaml(currProj + configFilePath);
    return configFile["uvm_components"][field].as<string>();
}



