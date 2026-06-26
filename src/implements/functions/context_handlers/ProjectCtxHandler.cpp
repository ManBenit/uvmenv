#include "../../../headers/functions/context_handlers/ProjectCtxHandler.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/uvmenv_handling/component_handling/create_component.h"

#include <vector>
#include <string>
using namespace std;

// public
int ProjectCtxHandler::cmdProject(const vector<string>& args){
    if( !requireProject() ) return 3;

    // ================================
    // Double validation of args
    // Required [1]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& warMsg = "Usage: uvmenv project <option>";
    if(args.size() < 2){
        printWarning(warMsg); 
        return 6;
    }
    if(!requireArgs({args[1]}, warMsg) ) return 6;
    // ================================

    
    if(args[1] == "view")        return this->runView();
    else if(args[1] == "init")   return this->runInit();
    else if(args[1] == "run")    return this->runRun();
    else if(args[1] == "show"){
        // ================================
        // Double validation of args
        // Required [1]
        // ================================
        // 1. Validate existance of required arguments and arguments not empty
        const string& warMsg = "Missing option: wave | report | coverage";
        if(args.size() < 3){
            printWarning(warMsg); 
            return 6;
        }
        if(!requireArgs({args[2]}, warMsg) ) return 6;
        // ================================
        
        return this->runShow(args[2]);
    }
    else {
        printError("[project] Unknown opt: " + args[1]);
        return 5;
    }

    return 0;
}


// private
int ProjectCtxHandler::runInit(){
    if( !requireDUT() ) return 4;

    getDUTSignals('r');
    createBFM("default");
    createTest("default");
    createEnvironmentOnTest("default", "TestDefault");
    createRefModel("default", "TestDefault", "EnvDefault");
    createSeqitem("default", "TestDefault");
    createSequence("default", "TestDefault");
    createAgent("default", "TestDefault", "EnvDefault");
    createScoreboard("default", "TestDefault", "EnvDefault");

    return 0;
}

int ProjectCtxHandler::runView(){
    showProjectTree();
    return 0;
}

int ProjectCtxHandler::runRun(){
    if( !requireDUT() ) return 4;

    runCurrentProject();
    return 0;
}

int ProjectCtxHandler::runShow(const string& showOption){
    if(showOption == "coverage"){
        showCoverage();
    }
    else if(showOption == "report"){
        showReport();
    }
    else if(showOption == "wave"){
        showWaveform();
    }
    
    else {
        printError("[project] Unknown comp: " + showOption);
        return 5;
    }
    
    return 0;
}


