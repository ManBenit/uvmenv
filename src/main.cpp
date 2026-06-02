#include "test_main.h" // Ommit to prod
#include "headers/functions/utils.h"
#include "headers/functions/context_handlers/ComponentCtxHandler.h"
#include "headers/functions/context_handlers/ImmediateCtxHandler.h"
#include "headers/functions/context_handlers/ProjectCtxHandler.h"
using namespace std;


int main (int argc, char *argv[]) {
    vector<string> args;
    for(int i=1; i<argc; i++)
        args.push_back(argv[i]);

    ComponentCtxHandler compCtxHandlr;
    ImmediateCtxHandler immCtxHandlr;
    ProjectCtxHandler projCtxHandlr;
    string ctx = args[0];

    printInfo("UVMEnv 2.0 - TESTING/DEVELOPING");
    if(argc < 2) return immCtxHandlr.cmdHelp();    
    
    ///// FRAMEWORK HANDLING /////
    if(ctx == "new") {
        return immCtxHandlr.cmdNew(args);
    } 
    else if(ctx == "search") {
        return immCtxHandlr.cmdSearch();
    } 
    else if(ctx == "help") {
        return immCtxHandlr.cmdHelp();
    }

    ///// PROJECT HANDLING /////
    else if(ctx == "project"){
        return projCtxHandlr.cmdProject(args);
    }
    
    ///// COMPONENT HANDLING /////
    else if(ctx == "component"){
        return compCtxHandlr.cmdComponent(args);
    }

    else if(ctx == "test") {
        //component_creation_test();
        //getting_signals_test();

        //print( joinStr({"uno", "otro"}, ".") );
    }

    else {
        printError("Unknown ctx: " + ctx);
        return 5;
    }

    return 0;
}



