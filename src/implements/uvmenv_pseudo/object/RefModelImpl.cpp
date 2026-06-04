#include "../../../headers/uvmenv_pseudo/objects/RefModelImpl.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
using namespace std;


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
    vector<string> parameters;
    vector<string> assigns;
    vector<string> returns;

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    for(const auto& [signalName, signalProps] : dutSignals) {
        for (const auto& signal : signalProps) {
            if(signal.type == "INPUT"){
                parameters.push_back(signal.name);
                assigns.push_back(
                    doTabs(2)+"self." + signal.name + " = " + signal.name
                );
            }
            else if(signal.type == "OUTPUT"){
                returns.push_back(
                    doTabs(3)+"'"+signal.name + "': None"
                );
            }
        }
    }
    // Modify 'set_inputs' method (parameters)
    content = regex_replace(content, regex("PARAMETERS"), joinStr(parameters, ", ") );
    
    // Modify 'set_inputs' method (inits)
    content = regex_replace(content, regex("PARAMS_ASSIGNS"), joinStr(assigns, "\n") );

    // Modify set test make_test method (for Python and Verilator)
    content = regex_replace(content, regex("RETURNS"), joinStr(returns, ",\n") );


    // Write project file
    ofstream testFile(joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "RefMdl", "_impl", name+".py"
    }, PATH_SEP));
    testFile << content;
}


// private
ObjectRegister<RefModelImpl> RefModelImpl::reg("RefModelImpl");


