#include <iostream>
#include <cstdlib>

#include "headers/functions/utils.h"
#include "headers/functions/constants.h"
#include "headers/uvmenv_handling/general_handling/framework.h"
#include "headers/uvmenv_handling/component_handling/create_component.h"
#include "headers/uvmenv_handling/component_handling/list_component.h"
#include "headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "test_main.h" // Ommit to prod
using namespace std;




int main (int argc, char *argv[]) {
    cout << C_GREEN << "UVMEnv 2.0 - TESTING/DEVELOPING" << C_N << endl;
    if(argc < 2) {
        showHelp();
        return 0;
    }

    string option = argv[1];
    
    ///// FRAMEWORK HANDLING /////
    if(option == "new") {

        if(argv[2] == nullptr || argv[3] == nullptr){
            printError("Missing parameters");
            printInfo("Usage: uvmenv -n|--new <project name> <top module name>");
            exit(0);
        }

        // argv[2]: Project name.
        // argv[3]: Top module name.
        createNewEnv(argv[2], argv[3]);
    } 
    else if(option == "search") {
        if(isUVMEnvProject(PROJECT_DIR)){
            printInfo("You are already into a UVMEnv project");
            return 0;
        }

        searchProjects();
    } 
    else if(option == "help") {
        showHelp();
    }


    ///// PROJECT HANDLING /////
    else if(option == "project"){
        if(!isUVMEnvProject(PROJECT_DIR)){
            printError("You need using a valid project to run this option.");
            return 1;
        }

        if(argv[2] == nullptr){
            printError("Missing project option");
            return 4;
        }

        
        if(string(argv[2]) == "view"){
            showProjectTree();
        }
        else if(string(argv[2]) == "init"){
            if(!existsDUT()){
                printError("DUT files not found.");
                return 1;
            }
            cout << "Initializing project..." << endl;
        }
        else if(string(argv[2]) == "report"){
            showReport();
        }
        else if(string(argv[2]) == "wave"){
            cout << "Show waveform..." << endl;
            //showWaveform();
        }
        else if(string(argv[2]) == "run"){
            if(!existsDUT()){
                printError("DUT files not found.");
                return 3;
            }
            runCurrentProject();
        }
        else {
            printError("Unknown project option: " + string(argv[2]));
            return 2;
        }
    }
    

    ///// COMPONENT HANDLING /////
    else if(option == "component"){
        if(!isUVMEnvProject(PROJECT_DIR)){
            printError("You need using a valid project to run this option.");
            return 1;
        }

        if(!existsDUT()){
            printError("DUT files not found.");
            return 1;
        }

        if(argv[2] == nullptr){
            printError("USAGE: uvmenv component OPTION COMPONENT ATTRIBUTES");
            printInfo("See uvmenv help for more details");
            return 4;
        }

        if(argv[3] == nullptr){
            printError("Missing component reference");
            return 4;
        }

        
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
                cout << "webos" << endl;
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
            printError("Unknown component option: " + string(argv[2]));
            return 2;
        }
        
    }

    else if(option == "test") {
        component_creation_test();
        getting_signals_test();
    }

    else {
        printError("Unknown option: " + option);
        return 2;
    }

    return 0;
}


