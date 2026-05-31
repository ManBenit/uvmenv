#include "../../../headers/functions/context_handlers/ComponentCtxHandler.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/uvmenv_handling/component_handling/create_component.h"
#include "../../../headers/uvmenv_handling/component_handling/list_component.h"
using namespace std;


// public
int ComponentCtxHandler::cmdComponent(const vector<string>& args){
    if( !requireProject() ) return 3;
    if( !requireDUT() ) return 4;

    // ================================
    // Double validation of args
    // Required [1, 2]
    // ================================
    // 1. Validate existance of required arguments
    if(args.size() < 3){
        printWarning("USAGE: uvmenv component OPTION COMPONENT ATTRIBUTES");
        return 6;
    }
    // 2. Validate arguments not empty
    if( !requireArgs(
        {args[1], args[2]},
        "USAGE: uvmenv component OPTION COMPONENT ATTRIBUTES"
    ) ) return 6;
    // ================================

    
    if(string(args[1]) == "create")      return this->runCreate(args);
    else if(string(args[1]) == "delete") return this->runDelete(args);
    else if(string(args[1]) == "edit")   return this->runEdit(args);
    else if(string(args[1]) == "list")   return this->runList(args);
    else {
        printError("[component] Unknown ctx: " + string(args[1]));
        return 5;
    }

    return 0;
}


// private
int ComponentCtxHandler::runCreate(const vector<string>& args){
    /** 
     * For listing components, consider:
     * - args[2]: Component you want.
     * - args[3]: Component name.
     * - args[4]: Test name in which your component is.
     * - args[5]: Env name in which your component is.
     */
    if( string(args[2]) == "test" ){
        createTest(args[3]);
    }
    else if( string(args[2]) == "bfm" ){
        createBFM(args[3]);
    }
    else if( string(args[2]) == "env" ){
        createEnvironmentOnTest(args[3], args[4]);
    }
    else if( string(args[2]) == "seqitem" ){
        createSeqitem          (args[3], args[4]);
    }
    else if( string(args[2]) == "seqce" ){
        createSequence         (args[3], args[4]);
    }
    else if( string(args[2]) == "agent" ){
        createAgent            (args[3], args[4], args[5]);
    }
    else if( string(args[2]) == "scorebd" ){
        createScoreboard       (args[3], args[4], args[5]);
    }
    else if( string(args[2]) == "refmod" ){
        createRefModel         (args[3], args[4], args[5]);
    }

    return 0;
}

int ComponentCtxHandler::runList(const vector<string>& args){
    /** 
     * For listing components, consider:
     * - args[2]: Component you want.
     * - args[3]: Test name in which your component is.
     * - args[4]: Env name in which your component is.
     */
    if( string(args[2]) == "test" ){
        for(const string& s: listTests())
            print(s);
    }
    else if( string(args[2]) == "bfm" ){
        for(const string& s: listBFMInterfaces())
            print(s);
    }
    else if( string(args[2]) == "env" ){
        for(const string& s: listEnvsOnTest (args[3]))
            print(s);
    }
    else if( string(args[2]) == "seqitem" ){
        for(const string& s: listSeqitems   (args[3]))
            print(s);
    }
    else if( string(args[2]) == "seqce" ){
        for(const string& s: listSequences  (args[3]))
            print(s);
    }
    else if( string(args[2]) == "agent" ){
        for(const string& s: listAgents     (args[3], args[4]))
            print(s);
    }
    else if( string(args[2]) == "scorebd" ){
        for(const string& s: listScoreboards(args[3], args[4]))
            print(s);
    }
    else if( string(args[2]) == "refmod" ){
        for(const string& s: listRefModels  (args[3], args[4]))
            print(s);
    }
    
    else if( string(args[2]) == "misc" ){
        print("Comming soon...");
    }
    else if( string(args[2]) == "rtlsig" ){

    }
    else if( string(args[2]) == "rtlmod" ){

    }

    return 0;
}

int ComponentCtxHandler::runDelete(const vector<string>& args){
    return 0;
}

int ComponentCtxHandler::runEdit(const vector<string>& args){
    return 0;
}



