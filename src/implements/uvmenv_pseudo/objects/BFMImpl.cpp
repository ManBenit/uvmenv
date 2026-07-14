#include <iostream>
#include "../../../headers/uvmenv_pseudo/objects/BFMImpl.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <regex>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


//
void BFMImpl::setName(const string& name){
    this->name = name;
}

void BFMImpl::editFile(const string& name){
    const string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDirPrefix  + PATH_SEP +  name+".py";

    if(!filesystem::exists(uvmenvProjectDir)){
        printError("[BFM] Does not exist " + name);
        exit(5);
    }

    int sysResult = system(file.c_str());
    if (sysResult== 0) {
        printInfo("Finished edition of " + name);
    } else {
        printError( "Something went wrong while editing " + name + ". Returned code " + to_string(sysResult) );
    }
}

void BFMImpl::deleteFile(const string& name){
    const string toDelete = uvmenvProjectDirPrefix  + PATH_SEP +  name+".py";

    if(!filesystem::exists(toDelete)){
        printError("[BFM] Does not exist " + name);
        exit(5);
    }

    filesystem::remove(toDelete);
}


// @Override
void BFMImpl::copyBaseFile(){
    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
    vector<string> req_values;
    vector<string> res_values;

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);


    json config = readFileJson(joinStr({
        PROJECT_DIR, "config.json"
    }, PATH_SEP));
    string topModule = config["dut_design"]["top_module"];
    
    for(const auto& [module, signalProps] : dutSignals) {
        // Create file content only with top module signals
        if(module == topModule){
            for (const auto& signal : signalProps) {
                if(signal.type == "INPUT"){
                    req_values.push_back(
                        doTabs(2)+"self.dut." + signal.name + ".value = self.__transaction." + signal.name
                    );
                }
                else if(signal.type == "OUTPUT"){
                    res_values.push_back(
                        doTabs(2)+"self.__transaction." + signal.name + " = self.dut." + signal.name + ".value"
                    );
                }
            }
        }
    }
    // Modify 'set' method
    content = regex_replace(content, regex("ASSIGN_REQ_VALUES"), joinStr(req_values, "\n") );

    // Modify 'get' method
    content = regex_replace(content, regex("ASSIGN_RES_VALUES"), joinStr(res_values, "\n") );

    // Write project file
    ofstream outFile(uvmenvProjectDir);
    outFile << content;
    outFile.close();
}


// private
ObjectRegister<BFMImpl> BFMImpl::reg("BFMImpl");


