#include <iostream>
#include <cstdlib>
#include <initializer_list>

#include "headers/functions/utils.h"
#include "headers/functions/constants.h"
#include "headers/uvmenv_handling/general_handling/framework.h"
#include "headers/uvmenv_handling/component_handling/create_component.h"
#include "headers/uvmenv_handling/component_handling/list_component.h"
#include "headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "test_main.h" // Ommit to prod

#include "headers/functions/context_handlers/ComponentCtxHandler.h"
#include "headers/functions/context_handlers/ImmediateCtxHandler.h"
#include "headers/functions/context_handlers/ProjectCtxHandler.h"
using namespace std;



int main (int argc, char *argv[]) {
    vector<string> args;
    for(int i=1; i<argc; i++)
        args.push_back(argv[i]);

    cout << C_GREEN << "UVMEnv 2.0 - TESTING/DEVELOPING" << C_N << endl;
    if(argc < 2) {
        showHelp();
        return 0;
    }

    ComponentOptHandler compOptHandlr;
    ImmediateOptHandler immOptHandlr;
    ProjectOptHandler projOptHandlr;

    string ctx = args[0];
    
    ///// FRAMEWORK HANDLING /////
    if(ctx == "new") {
        return immOptHandlr.cmdNew(args);
    } 
    else if(ctx == "search") {
        return immOptHandlr.cmdSearch();
    } 
    else if(ctx == "help") {
        return immOptHandlr.cmdHelp();
    }


    ///// PROJECT HANDLING /////
    else if(ctx == "project"){
        if( !requireProject() ) return 3;
        if( !requireArgs({argv[2]}, "Missing project ctx") ) return 6;

        
        if(string(argv[2]) == "view"){
            showProjectTree();
        }

        else if(string(argv[2]) == "init"){
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
            
        }
        else if(string(argv[2]) == "report"){
            showReport();
        }
        else if(string(argv[2]) == "wave"){
            cout << "Show waveform..." << endl;
            //showWaveform();
        }
        else if(string(argv[2]) == "run"){
            if( !requireDUT() ) return 4;
            runCurrentProject();
        }
        else {
            printError("[project] Unknown ctx: " + string(argv[2]));
            return 5;
        }
    }
    

    ///// COMPONENT HANDLING /////
    else if(ctx == "component"){
        if( !requireProject() ) return 3;
        if( !requireDUT() ) return 4;
        if( !requireArgs(
            {argv[2], argv[3]}, 
            "USAGE: uvmenv component OPTION COMPONENT ATTRIBUTES"
        ) ) return 6;

        
        if(string(argv[2]) == "create"){
            cout << "Creating component..." << endl;
            cout << "Component type: " << argv[3] << endl;
            
            /** 
             * For listing components, consider:
             * - argv[3]: Component you want.
             * - argv[4]: Component name.
             * - argv[5]: Test name in which your component is.
             * - argv[6]: Env name in which your component is.
             */
            if( string(argv[3]) == "test" ){
                createTest(argv[4]);
            }
            else if( string(argv[3]) == "bfm" ){
                createBFM(argv[4]);
            }
            else if( string(argv[3]) == "env" ){
                createEnvironmentOnTest(argv[4], argv[5]);
            }
            else if( string(argv[3]) == "seqitem" ){
                createSeqitem          (argv[4], argv[5]);
            }
            else if( string(argv[3]) == "seqce" ){
                createSequence         (argv[4], argv[5]);
            }
            else if( string(argv[3]) == "agent" ){
                createAgent            (argv[4], argv[5], argv[6]);
            }
            else if( string(argv[3]) == "scorebd" ){
                createScoreboard       (argv[4], argv[5], argv[6]);
            }
            else if( string(argv[3]) == "refmod" ){
                createRefModel         (argv[4], argv[5], argv[6]);
            }
        }
        else if(string(argv[2]) == "delete"){

        }
        else if(string(argv[2]) == "edit"){
            
        }
        else if(string(argv[2]) == "list"){
            /** 
             * For listing components, consider:
             * - argv[3]: Component you want.
             * - argv[4]: Test name in which your component is.
             * - argv[5]: Env name in which your component is.
             */
            if( string(argv[3]) == "test" ){
                for(const string& s: listTests())
                    cout << s << endl;
            }
            else if( string(argv[3]) == "bfm" ){
                for(const string& s: listBFMInterfaces())
                    cout << s << endl;
            }
            else if( string(argv[3]) == "env" ){
                for(const string& s: listEnvsOnTest (argv[4]))
                    cout << s << endl;
            }
            else if( string(argv[3]) == "seqitem" ){
                for(const string& s: listSeqitems   (argv[4]))
                    cout << s << endl;
            }
            else if( string(argv[3]) == "seqce" ){
                for(const string& s: listSequences  (argv[4]))
                    cout << s << endl;
            }
            else if( string(argv[3]) == "agent" ){
                for(const string& s: listAgents     (argv[4], argv[5]))
                    cout << s << endl;
            }
            else if( string(argv[3]) == "scorebd" ){
                for(const string& s: listScoreboards(argv[4], argv[5]))
                    cout << s << endl;
            }
            else if( string(argv[3]) == "refmod" ){
                for(const string& s: listRefModels  (argv[4], argv[5]))
                    cout << s << endl;
            }
            
            else if( string(argv[3]) == "misc" ){
                cout << "Comming soon..." << endl;
            }
            else if( string(argv[3]) == "rtlsig" ){

            }
            else if( string(argv[3]) == "rtlmod" ){

            }

        }
        else {
            printError("[component] Unknown ctx: " + string(argv[2]));
            return 5;
        }
        
    }

    else if(ctx == "test") {
        component_creation_test();
        getting_signals_test();
    }

    else {
        printError("Unknown ctx: " + ctx);
        return 5;
    }

    return 0;
}



