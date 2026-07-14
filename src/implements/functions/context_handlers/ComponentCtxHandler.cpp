#include "../../../headers/functions/context_handlers/ComponentCtxHandler.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/uvmenv_handling/component_handling/create_component.h"
#include "../../../headers/uvmenv_handling/component_handling/edit_component.h"
#include "../../../headers/uvmenv_handling/component_handling/list_component.h"
using namespace std;


// public
int ComponentCtxHandler::cmdComponent(const vector<string>& args, const string& test, const string& env, const string& module, const string& type){
    if( !requireProject() ) return 3;
    if( !requireDUT() ) return 4;

    // ================================
    // Double validation of args
    // Required [0,1]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& warMsg = "Usage: uvmenv component < create | delete | edit | list >";
    if(args.size() < 2){
        printWarning(warMsg); 
        return 6;
    }
    if(!requireArgs({args[0], args[1]}, warMsg) ) return 6;
    // ================================

    
    if(string(args[1]) == "create")      return this->runCreate(args, test, env, module, type);
    else if(string(args[1]) == "delete") return this->runDelete(args);
    else if(string(args[1]) == "edit")   return this->runEdit(args, test, env);
    else if(string(args[1]) == "list")   return this->runList(args, test, env);
    else {
        printError("[component] Unknown opt: " + string(args[1]));
        return 5;
    }

    return 0;
}


// private
int ComponentCtxHandler::runCreate(const vector<string>& args, const string& test, const string& env, const string& module, const string& type){
    // ================================
    // Double validation of args
    // Required [3]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& warMsg = "Missing cmponent name. Usage: uvmenv component create < CRT_OPTS > <name>";
    if(args.size() < 4){
        printWarning(warMsg); 
        return 6;
    }
    if(!requireArgs({args[2], args[3]}, warMsg) ) return 6;
    // ================================
    const string missTestMsg = "Missing name of parent Test";
    const string missEnvMsg = "Missing name of parent Environment";

    const string comp = args[2];
    const string name = args[3];

    if( comp == "test" ){
        createTest(name);
    }
    else if( comp == "bfm" ){
        createBFM(name);
    }
    else if( comp == "env" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        createEnvironmentOnTest(name, test);
    }
    else if( comp == "seqitem" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        createSeqitem          (name, test);
    }
    else if( comp == "seqce" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        createSequence         (name, test);
    }
    else if( comp == "agent" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        createAgent            (name, test, env, type);
    }
    else if( comp == "scorebd" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        createScoreboard       (name, test, env);
    }
    else if( comp == "refmod" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        createRefModel         (name, test, env);
    }
    else {
        printError("[component] Unknown comp: " + comp);
        return 5;
    }

    return 0;
}

int ComponentCtxHandler::runList(const vector<string>& args, const string& test, const string& env){
    // ================================
    // Double validation of args
    // Required [3]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& warMsg = "Missing cmponent name. Usage: uvmenv component list < LST_OPTS >";
    if(args.size() < 3){
        printWarning(warMsg); 
        return 6;
    }
    if(!requireArgs({args[2]}, warMsg) ) return 6;
    // ================================
    const string missTestMsg = "Missing name of parent Test";
    const string missEnvMsg = "Missing name of parent Environment";

    const string comp = args[2];

    if( comp == "test" ){
        for(const string& s: listTests())
            print(s);
    }
    else if( comp == "bfm" ){
        for(const string& s: listBFMInterfaces())
            print(s);
    }
    else if( comp == "env" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        for(const string& s: listEnvsOnTest (test))
            print(s);
    }
    else if( comp == "seqitem" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        for(const string& s: listSeqitems   (test))
            print(s);
    }
    else if( comp == "seqce" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        for(const string& s: listSequences  (test))
            print(s);
    }
    else if( comp == "agent" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        for(const string& s: listAgents     (test, env))
            print(s);
    }
    else if( comp == "scorebd" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        for(const string& s: listScoreboards(test, env))
            print(s);
    }
    else if( comp == "refmod" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        for(const string& s: listRefModels  (test, env))
            print(s);
    }
    
    else if( comp == "misc" ){
        print("Comming soon, list Misces directory...");
    }
    else if( comp == "rtlsig" ){
        print("Comming soon, list RTL signals with/wothout filtering...");

    }
    else if( comp == "rtlmod" ){
        print("Comming soon, list RTL modules...");

    }
    else {
        printError("[component] Unknown comp: " + comp);
        return 5;
    }

    return 0;
}

int ComponentCtxHandler::runDelete(const vector<string>& args){
    return 0;
}

int ComponentCtxHandler::runEdit(const vector<string>& args, const string& test, const string& env){
    // ================================
    // Double validation of args
    // Required [3]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& warMsg = "Missing cmponent name. Usage: uvmenv component edit < CRT_OPTS > <name>";
    if(args.size() < 4){
        printWarning(warMsg); 
        return 6;
    }
    if(!requireArgs({args[2], args[3]}, warMsg) ) return 6;
    // ================================
    const string missTestMsg = "Missing name of parent Test";
    const string missEnvMsg = "Missing name of parent Environment";

    const string comp = args[2];
    const string name = args[3];

    if( comp == "test" ){
        print("Noyet");
        // createTest(name);
    }
    else if( comp == "bfm" ){
        editBFM(name);
    }
    // else if( comp == "env" ){
    //     if(!requireArgs({test}, missTestMsg) ) return 6;
    //     createEnvironmentOnTest(name, test);
    // }
    // else if( comp == "seqitem" ){
    //     if(!requireArgs({test}, missTestMsg) ) return 6;
    //     createSeqitem          (name, test);
    // }
    // else if( comp == "seqce" ){
    //     if(!requireArgs({test}, missTestMsg) ) return 6;
    //     createSequence         (name, test);
    // }
    // else if( comp == "agent" ){
    //     if(!requireArgs({test}, missTestMsg) ) return 6;
    //     if(!requireArgs({env}, missEnvMsg) ) return 6;
    //     createAgent            (name, test, env, type);
    // }
    // else if( comp == "scorebd" ){
    //     if(!requireArgs({test}, missTestMsg) ) return 6;
    //     if(!requireArgs({env}, missEnvMsg) ) return 6;
    //     createScoreboard       (name, test, env);
    // }
    // else if( comp == "refmod" ){
    //     if(!requireArgs({test}, missTestMsg) ) return 6;
    //     if(!requireArgs({env}, missEnvMsg) ) return 6;
    //     createRefModel         (name, test, env);
    // }
    else {
        printError("[component] Unknown comp: " + comp);
        return 5;
    }

    return 0;
}



