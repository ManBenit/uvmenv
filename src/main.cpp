#include "headers/functions/utils.h"
#include "headers/functions/context_handlers/ComponentCtxHandler.h"
#include "headers/functions/context_handlers/ImmediateCtxHandler.h"
#include "headers/functions/context_handlers/ProjectCtxHandler.h"
using namespace std;

int main (int argc, char *argv[]) {
    ComponentCtxHandler compCtxHandlr;
    ImmediateCtxHandler immCtxHandlr;
    ProjectCtxHandler projCtxHandlr;
    
    if(argc == 1){
        return immCtxHandlr.cmdHelp();
    }

    string mod = "";
    string test = "";
    string env = "";
    string wlevel = "";
    string type = "";
    vector<string> args;

    for(int i=1; i<argc; i++){
        if(string(argv[i]) == "--module"){
            mod = argv[i+1];
            i++;
        }
        else if(string(argv[i]) == "--test"){
            test = argv[i+1];
            i++;
        }
        else if(string(argv[i]) == "--type"){
            type = argv[i+1];
            i++;
        }
        else if(string(argv[i]) == "--env"){
            env = argv[i+1];
            i++;
        }
        // TODO: Add functionality to this option to set wave level for GTKWave
        else if(string(argv[i]) == "--wave-level"){
            wlevel = argv[i+1];
            i++;
        }
        else{
            args.push_back(argv[i]);
        }
    }

    if(args.size() == 0){
        return immCtxHandlr.cmdHelp();
    }

    
    string ctx = args[0];

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
        return projCtxHandlr.cmdProject(args, wlevel);
    }
    
    ///// COMPONENT HANDLING /////
    else if(ctx == "component"){
        return compCtxHandlr.cmdComponent(args, test, env, mod, type);
    }

    else {
        printError("Unknown ctx: " + ctx);
        return 5;
    }

    return 0;
}
