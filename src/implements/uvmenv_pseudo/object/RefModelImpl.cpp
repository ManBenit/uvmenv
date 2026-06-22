#include "../../../headers/uvmenv_pseudo/objects/RefModelImpl.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


void RefModelImpl::setName(const string& name){
    this->name = name;
}

void RefModelImpl::setTestContainer(const string& testName){
    this->testName = testName;
}

void RefModelImpl::setEnvContainer(const string& envName){
    this->envName = envName;
}


// @Override
void RefModelImpl::copyBaseFile(){
    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
    vector<string> trOuts;
    vector<string> assigns;
    vector<string> returns;

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);


    json config = readFileJson(joinStr({
        PROJECT_DIR, "config.json"
    }, PATH_SEP));
    string topModule = config["dut_design"]["top_module"];

    for(const auto& [module, signalProps] : dutSignals) 
        // Create file content only with top module signals
        if(module == topModule)
            for (const auto& signal : signalProps) 
                if(signal.type == "OUTPUT")
                    trOuts.push_back(
                        doTabs(2)+"self.__transaction." + signal.name + " = 0"
                    );
    
    // Modify '__do_with_python' and '__do_with_verilator' methods
    content = regex_replace(content, regex("TRANSACTION_OUTS"), joinStr(trOuts, "\n") );

    // Write project file
    ofstream testFile(joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "RefMdl", "_impl", name+".py"
    }, PATH_SEP));
    testFile << content;
}


// private
ObjectRegister<RefModelImpl> RefModelImpl::reg("RefModelImpl");


