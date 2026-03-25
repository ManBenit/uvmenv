#include "headers/functions/utils.h"
#include "headers/functions/constants.h"

#include "headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "headers/uvmenv_handling/general_handling/framework.h"

#include "headers/uvmenv_preudo/Factory.h"
#include "headers/uvmenv_preudo/components/Top.h"
#include "headers/uvmenv_preudo/UVMObject.h"
#include "headers/uvmenv_preudo/UVMComponent.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>
using namespace std;

// NOTE: Include sudo apt install nlohmann-json3-dev on install script.

void uvm_test();


int main (int argc, char *argv[]) {
    cout << C_GREEN << "UVMEnv 2.0 - TESTING/DEVELOPING" << C_N << endl;
    activatePythonVenv();

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
            execCmdSimple(getScript("sys_commands")+"viewTreeProject");
        }
        else if(string(argv[2]) == "init"){

        }
        else if(string(argv[2]) == "report"){
            execCmdSimple(getScript("sys_commands")+"viewReport");
        }
        else if(string(argv[2]) == "wave"){
            execCmdSimple(getScript("sys_commands")+"runGTKWave");
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

        if(argv[2] == nullptr){
            printError("uvmenv -c|--create agnt <attr> <agent_name> <module>");
            return 4;
        }

        if(argv[3] == nullptr){
            printError("Missing component reference");
            return 4;
        }
        else{
            // Validate component existence 
            cout << "Validate component existence" << endl;
        }

        
        if(argv[2] == "create"){
            
        }
        else if(argv[2] == "delete"){

        }
        else if(argv[2] == "edit"){
            
        }
        else if(argv[2] == "list"){
            
        }
        else {
            printError("Unknown component option: " + string(argv[2]));
            return 2;
        }
        
    }

    else if(option == "test") {
        
    }

    else {
        printError("Unknown option: " + option);
        return 2;
    }

    return 0;
}



void uvm_test(){
    UVMComponent* top = &Top::instance();


    //------------------------------------------------------
    // TEST 1
    //------------------------------------------------------
    UVMComponent* test1 = Factory::instance().createComponent("Test","Test_A",top);

    // Environments
    UVMComponent* env1 = Factory::instance().createComponent("Environment","Env_A1",test1);
    UVMComponent* env2 = Factory::instance().createComponent("Environment","Env_A2",test1);


    // ---- ENV A1 ----
    UVMComponent* agtA1 = Factory::instance().createComponent("Agent","Agent_A1",env1);

    UVMComponent* drvA1 = Factory::instance().createComponent("Driver","Driver_A1",agtA1);
    UVMComponent* monA1 = Factory::instance().createComponent("Monitor","Monitor_A1",agtA1);
    UVMComponent* covA1 = Factory::instance().createComponent("Coverage","Coverage_A1",agtA1);

    UVMComponent* scbA1 = Factory::instance().createComponent("Scoreboard","Scoreboard_A1",env1);


    // ---- ENV A2 ----
    UVMComponent* agtA2 = Factory::instance().createComponent("Agent","Agent_A2",env2);

    UVMComponent* drvA2 = Factory::instance().createComponent("Driver","Driver_A2",agtA2);
    UVMComponent* monA2 = Factory::instance().createComponent("Monitor","Monitor_A2",agtA2);
    UVMComponent* covA2 = Factory::instance().createComponent("Coverage","Coverage_A2",agtA2);

    UVMComponent* scbA2 = Factory::instance().createComponent("Scoreboard","Scoreboard_A2",env2);



    //------------------------------------------------------
    // TEST 2
    //------------------------------------------------------
    UVMComponent* test2 = Factory::instance().createComponent("Test","Test_B",top);

    // Environments
    UVMComponent* env3 = Factory::instance().createComponent("Environment","Env_B1",test2);
    UVMComponent* env4 = Factory::instance().createComponent("Environment","Env_B2",test2);

    // ---- ENV B1 ----
    UVMComponent* agtB1 = Factory::instance().createComponent("Agent","Agent_B1",env3);

    UVMComponent* drvB1 = Factory::instance().createComponent("Driver","Driver_B1",agtB1);
    UVMComponent* monB1 = Factory::instance().createComponent("Monitor","Monitor_B1",agtB1);
    UVMComponent* covB1 = Factory::instance().createComponent("Coverage","Coverage_B1",agtB1);

    UVMComponent* scbB1 = Factory::instance().createComponent("Scoreboard","Scoreboard_B1",env3);


    // ---- ENV B2 ----
    UVMComponent* agtB2 = Factory::instance().createComponent("Agent","Agent_B2",env4);

    UVMComponent* drvB2 = Factory::instance().createComponent("Driver","Driver_B2",agtB2);
    UVMComponent* monB2 = Factory::instance().createComponent("Monitor","Monitor_B2",agtB2);
    UVMComponent* covB2 = Factory::instance().createComponent("Coverage","Coverage_B2",agtB2);

    UVMComponent* scbB2 = Factory::instance().createComponent("Scoreboard","Scoreboard_B2",env4);



    //------------------------------------------------------
    // OBJECTS
    //------------------------------------------------------
    UVMObject* seqA = Factory::instance().createObject("Sequence","Seq_A");
    UVMObject* seqItemA = Factory::instance().createObject("SequenceItem","SeqItem_A");
    UVMObject* bfmA = Factory::instance().createObject("BFMImpl","BFM_A");
    UVMObject* refA = Factory::instance().createObject("RefModelImpl","RefModel_A");



    /********************************************************
     *
     * COPY BASEFILE
     *
     ********************************************************/

    top->copyBaseFile();
    test1->copyBaseFile();
    env1->copyBaseFile();
    env2->copyBaseFile();

    agtA1->copyBaseFile();
    drvA1->copyBaseFile();
    monA1->copyBaseFile();
    covA1->copyBaseFile();
    scbA1->copyBaseFile();

    agtA2->copyBaseFile();
    drvA2->copyBaseFile();
    monA2->copyBaseFile();
    covA2->copyBaseFile();
    scbA2->copyBaseFile();



    test2->copyBaseFile();
    env3->copyBaseFile();
    env4->copyBaseFile();

    agtB1->copyBaseFile();
    drvB1->copyBaseFile();
    monB1->copyBaseFile();
    covB1->copyBaseFile();
    scbB1->copyBaseFile();

    agtB2->copyBaseFile();
    drvB2->copyBaseFile();
    monB2->copyBaseFile();
    covB2->copyBaseFile();
    scbB2->copyBaseFile();


    // Objects

    seqA->copyBaseFile();
    seqItemA->copyBaseFile();
    bfmA->copyBaseFile();
    refA->copyBaseFile();



    /********************************************************
     *
     * PRINT TREE
     *
     ********************************************************/

    cout << top << endl;
    cout << test1 << endl;
    
    cout << env1 << endl;
    cout << agtA1 << endl;
    cout << drvA1 << endl;
    cout << monA1 << endl;
    cout << covA1 << endl;
    cout << scbA1 << endl;
    
    cout << env2 << endl;
    cout << agtA2 << endl;
    cout << drvA2 << endl;
    cout << monA2 << endl;
    cout << covA2 << endl;
    cout << scbA2 << endl;
    

    cout << test2 << endl;
    
    cout << env3 << endl;
    cout << agtB1 << endl;
    cout << drvB1 << endl;
    cout << monB1 << endl;
    cout << covB1 << endl;
    cout << scbB1 << endl;
    
    cout << env4 << endl;
    cout << agtB2 << endl;
    cout << drvB2 << endl;
    cout << monB2 << endl;
    cout << covB2 << endl;
    cout << scbB2 << endl;


    // Objects

    cout << seqA << endl;
    cout << seqItemA << endl;
    cout << bfmA << endl;
    cout << refA << endl;
}

