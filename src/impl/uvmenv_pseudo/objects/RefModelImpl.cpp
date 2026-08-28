#include "../../../include/uvmenv_pseudo/objects/RefModelImpl.h"

#include "../../../include/functions/utils.h"
#include "../../../include/uvmenv_handling/general_handling/pconfig_handling.h"
#include "../../../include/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../include/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
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

void RefModelImpl::editFile(const string& name){
    uvmenvProjectDir = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "RefMdl", "_impl", name+".py"
    }, PATH_SEP);
    const string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDir;
    
    if(!filesystem::exists(uvmenvProjectDir)){
        printError("[Ref model] Does not exist " + name);
        exit(5);
    }
    
    int sysResult = system(file.c_str());
    if (sysResult== 0) {
        printInfo("Finished edition of " + name);
    } else {
        printError( "Something went wrong while editing " + name + ". Returned code " + to_string(sysResult) );
    }
}

void RefModelImpl::deleteFile(const string& name){
    const string toDelete = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "RefMdl", "_impl", name+".py"
    }, PATH_SEP);
    
    if(!filesystem::exists(toDelete)){
        printError("[Ref model] Does not exist " + name);
        exit(5);
    }
    
    filesystem::remove(toDelete);
}


// @Override
void RefModelImpl::copyBaseFile(){
    uvmenvProjectDir = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "RefMdl", "_impl", name+".py"
    }, PATH_SEP);


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

    string topModule = getProjectDutDesign(PROJECT_DIR, "top_module");

    for(const auto& [module, signalProps] : dutSignals) 
        // Create file content only with top module signals
        if(module == topModule)
            for (const auto& signal : signalProps) 
                if(signal.type == "OUTPUT")
                    trOuts.push_back(
                        doTabs(2)+"self.__transaction." + signal.name + " = to_bin_repr(0000000000000000, " + to_string(signal.size) +")"
                    );
    
    // Modify '__do_with_python' and '__do_with_verilator' methods
    content = regex_replace(content, regex("TRANSACTION_OUTS"), joinStr(trOuts, "\n") );

    // Write project file
    ofstream outFile(uvmenvProjectDir);
    outFile << content;
    outFile.close();
}


// private
ObjectRegister<RefModelImpl> RefModelImpl::reg("RefModelImpl");


