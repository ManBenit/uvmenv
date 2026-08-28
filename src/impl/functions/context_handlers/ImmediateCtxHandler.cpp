#include "../../../include/functions/context_handlers/ImmediateCtxHandler.h"

#include "../../../include/functions/utils.h"
#include "../../../include/functions/constants.h"
#include "../../../include/uvmenv_handling/general_handling/framework.h"

#include <vector>
#include <string>
#include <iostream> //
using namespace std;


// public
int ImmediateCtxHandler::cmdNew(const vector<string>& args){
    // ================================
    // Double validation of args
    // Required [1, 2]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& warMsg = "Usage: uvmenv new <project name> <top module name>";
    if(args.size() < 3){
        printWarning(warMsg); 
        return 6;
    }
    if(!requireArgs({args[1], args[2]}, warMsg) ) return 6;
    // ================================

    // argv[2]: Project name.
    // argv[3]: Top module name.
    createNewEnv(args[1], args[2]);

    return 0;
}

int ImmediateCtxHandler::cmdSearch(){
    if( isUVMEnvProject(PROJECT_DIR) ){
        printInfo("You are already into a UVMEnv project");
        return 0;
    }

    searchProjects();

    return 0;
}

int ImmediateCtxHandler::cmdHelp(){
    showHelp();
    return 0;
}


