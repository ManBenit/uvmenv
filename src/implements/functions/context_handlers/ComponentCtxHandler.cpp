#include "../../../headers/functions/context_handlers/ComponentCtxHandler.h"


#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/uvmenv_handling/component_handling/create_component.h"
#include "../../../headers/uvmenv_handling/component_handling/edit_component.h"
#include "../../../headers/uvmenv_handling/component_handling/list_component.h"
#include "../../../headers/uvmenv_handling/component_handling/delete_component.h"
#include <sstream>
using namespace std;

vector<string> options = {"test", "env", "agent", "seqitem", "seqce", "scorebd", "refmod", "bfm"};
const string& missTestMsg = "Missing name of parent Test. Use --test <name>";
const string& missEnvMsg = "Missing name of parent Environment. Use --env <name>";

// public
int ComponentCtxHandler::cmdComponent(const vector<string>& args, const string& test, const string& env, const string& module, const string& typeOrComp){
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

    
    if(string(args[1]) == "create")      return this->runCreate(args, test, env, module, typeOrComp); // type
    else if(string(args[1]) == "delete") return this->runDelete(args, test, env);
    else if(string(args[1]) == "edit")   return this->runEdit(args, test, env, typeOrComp); // comp
    else if(string(args[1]) == "list")   return this->runList(args, test, env, typeOrComp);
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
    const string& showOpts = joinStr(options, " | ");
    stringstream warMsg;
    warMsg << "Usage: uvmenv component create <comp> <name>\n";
    warMsg << doTabs(1) << "comp: " << showOpts;
    if(args.size() < 4){
        printWarning(warMsg.str()); 
        return 6;
    }
    if(!requireArgs({args[2], args[3]}, warMsg.str()) ) return 6;
    // ================================
    
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

int ComponentCtxHandler::runList(const vector<string>& args, const string& test, const string& env, const string& type){
    // ================================
    // Double validation of args
    // Required [3]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    options.push_back("misc");
    options.push_back("rtlsig");
    options.push_back("rtlmod");
    const string& showOpts = joinStr(options, " | ");
    stringstream warMsg;
    warMsg << "Usage: uvmenv component list <comp>\n";
    warMsg << doTabs(1) << "comp: " << showOpts;
    if(args.size() < 3){
        printWarning(warMsg.str()); 
        return 6;
    }
    if(!requireArgs({args[2]}, warMsg.str()) ) return 6;
    // ================================

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
        if(!requireArgs({test}, missTestMsg) ) return 6;
        for(const string& s: listMiscelaneous  (test))
            print(s);
    }
    else if( comp == "rtlsig" ){
        stringstream sigInfo;

        const bool isRefresh = toLowerCase(type) == "r" || toLowerCase(type) == "refresh";
        const auto& dutSignals = isRefresh ? refreshRtlSignals() : listRtlSignals();

        for(const auto& [module, signalProps] : dutSignals) {
            // Create file content only with top module signals
            printInfo("\tSignals of " + module);
            for (const auto& signal : signalProps) {
                sigInfo.str("");
                sigInfo.clear();
                sigInfo << signal.type << " [" << signal.size << " bits]: " << signal.name;
                print(sigInfo.str());
            }
        }
    }
    else if( comp == "rtlmod" ){
        for(const string& s: listRtlModules())
            print(s);
    }
    else {
        printError("[component] Unknown comp: " + comp);
        return 5;
    }

    return 0;
}

int ComponentCtxHandler::runDelete(const vector<string>& args, const string& test, const string& env){
    // ================================
    // Double validation of args
    // Required [3]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& showOpts = joinStr(options, " | ");
    stringstream warMsg;
    warMsg << "Usage: uvmenv component delete <comp> <name>\n";
    warMsg << doTabs(1) << "comp: " << showOpts;
    if(args.size() < 4){
        printWarning(warMsg.str()); 
        return 6;
    }
    if(!requireArgs({args[2], args[3]}, warMsg.str()) ) return 6;
    // ================================

    const string comp = args[2];
    const string name = args[3];

    if( comp == "test" ){
        deleteTest(name);
    }
    else if( comp == "bfm" ){
        deleteBFMInterface(name);
    }
    else if( comp == "env" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        deleteEnvOnTest(name, test);
    }
    else if( comp == "seqitem" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        deleteSeqitem          (name, test);
    }
    else if( comp == "seqce" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        deleteSequence         (name, test);
    }
    else if( comp == "agent" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        deleteAgent            (name, test, env);
    }
    else if( comp == "scorebd" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        deleteScoreboard       (name, test, env);
    }
    else if( comp == "refmod" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        deleteRefModel         (name, test, env);
    }
    else {
        printError("[component] Unknown comp: " + comp);
        return 5;
    }

    return 0;
}

int ComponentCtxHandler::runEdit(const vector<string>& args, const string& test, const string& env, const string& agntComponent){
    // ================================
    // Double validation of args
    // Required [3]
    // ================================
    // 1. Validate existance of required arguments and arguments not empty
    const string& showOpts = joinStr(options, " | ");
    stringstream warMsg;
    warMsg << "Usage: uvmenv component edit <comp> <name>\n";
    warMsg << doTabs(1) << "comp: " << showOpts;
    if(args.size() < 4){
        printWarning(warMsg.str()); 
        return 6;
    }
    if(!requireArgs({args[2], args[3]}, warMsg.str()) ) return 6;
    // ================================

    const string comp = args[2];
    const string name = args[3];

    if( comp == "test" ){
        editTest(name);
    }
    else if( comp == "bfm" ){
        editBFM(name);
    }
    else if( comp == "env" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        editEnvironmentOnTest(name, test);
    }
    else if( comp == "seqitem" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        editSeqitem          (name, test);
    }
    else if( comp == "seqce" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        editSequence         (name, test);
    }
    else if( comp == "agent" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        editAgent            (name, test, env, agntComponent);
    }
    else if( comp == "scorebd" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        editScoreboard       (name, test, env);
    }
    else if( comp == "refmod" ){
        if(!requireArgs({test}, missTestMsg) ) return 6;
        if(!requireArgs({env}, missEnvMsg) ) return 6;
        editRefModel         (name, test, env);
    }
    else {
        printError("[component] Unknown comp: " + comp);
        return 5;
    }

    return 0;
}



