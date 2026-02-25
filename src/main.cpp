#include "headers/functions/utils.h"
#include "headers/uvmenv_handling/general_handling/pre_project.h"
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
        searchProjects();
    } 
    else if(option == "help") {
        showHelp();
    }

    ///// PROJECT HANDLING /////
    else if(option == "project"){
        if(!isUVMEnvProject()){
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
        else if(argv[2] == "init"){

        }
        else if(argv[2] == "report"){
            execCmdSimple(getScript("sys_commands")+"viewReport");
        }
        else if(argv[2] == "wave"){
            execCmdSimple(getScript("sys_commands")+"runGTKWave");
        }
        else {
            printError("Unknown project option: " + string(argv[2]));
            return 2;
        }
    }
    
    ///// COMPONENT HANDLING /////
    else if(option == "component"){
        if(!isUVMEnvProject()){
            printError("You need using a valid project to run this option.");
            return 1;
        }

        if(argv[2] == nullptr){
            printError("Missing component option");
            return 4;
        }

        if(argv[3] == nullptr){
            printError("Missing component reference");
            return 4;
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
        UVMComponent* top = &Top::instance();
        UVMComponent* my_tst = Factory::instance().createComponent("Test", "Test_1", top);
        UVMComponent* my_scb = Factory::instance().createComponent("Scoreboard", "ScbdDefault_1", my_tst);
        top->copyBasefile();
        top->printInfo();
        my_tst->copyBasefile();
        my_tst->printInfo();
        my_scb->copyBasefile();
        my_scb->printInfo();

        UVMObject* seq1 = Factory::instance().createObject("Sequence", "MySeq1");
        seq1->copyBasefile();
        seq1->printInfo();
    }

    else if(option == "uvm_test"){
        uvm_test();
    }

    else {
        printError("Unknown option: " + option);
        return 2;
    }

    return 0;
}



void uvm_test(){
    //------------------------------------------------------
    // TOP 1
    //------------------------------------------------------

    UVMComponent* top = &Top::instance();

    UVMComponent* test1 =
        Factory::instance().createComponent("Test","Test_A",top);

    // Environments
    UVMComponent* env1 =
        Factory::instance().createComponent("Environment","Env_A1",test1);

    UVMComponent* env2 =
        Factory::instance().createComponent("Environment","Env_A2",test1);


    // ---- ENV A1 ----

    UVMComponent* agtA1 =
        Factory::instance().createComponent("Agent","Agent_A1",env1);

    UVMComponent* drvA1 =
        Factory::instance().createComponent("Driver","Driver_A1",agtA1);

    UVMComponent* monA1 =
        Factory::instance().createComponent("Monitor","Monitor_A1",agtA1);

    UVMComponent* covA1 =
        Factory::instance().createComponent("Coverage","Coverage_A1",agtA1);

    UVMComponent* scbA1 =
        Factory::instance().createComponent("Scoreboard","Scoreboard_A1",env1);


    // ---- ENV A2 ----

    UVMComponent* agtA2 =
        Factory::instance().createComponent("Agent","Agent_A2",env2);

    UVMComponent* drvA2 =
        Factory::instance().createComponent("Driver","Driver_A2",agtA2);

    UVMComponent* monA2 =
        Factory::instance().createComponent("Monitor","Monitor_A2",agtA2);

    UVMComponent* covA2 =
        Factory::instance().createComponent("Coverage","Coverage_A2",agtA2);

    UVMComponent* scbA2 =
        Factory::instance().createComponent("Scoreboard","Scoreboard_A2",env2);



    //------------------------------------------------------
    // TOP 2
    //------------------------------------------------------

    UVMComponent* test2 =
        Factory::instance().createComponent("Test","Test_B",top);


    // Environments

    UVMComponent* env3 =
        Factory::instance().createComponent("Environment","Env_B1",test2);

    UVMComponent* env4 =
        Factory::instance().createComponent("Environment","Env_B2",test2);


    // ---- ENV B1 ----

    UVMComponent* agtB1 =
        Factory::instance().createComponent("Agent","Agent_B1",env3);

    UVMComponent* drvB1 =
        Factory::instance().createComponent("Driver","Driver_B1",agtB1);

    UVMComponent* monB1 =
        Factory::instance().createComponent("Monitor","Monitor_B1",agtB1);

    UVMComponent* covB1 =
        Factory::instance().createComponent("Coverage","Coverage_B1",agtB1);

    UVMComponent* scbB1 =
        Factory::instance().createComponent("Scoreboard","Scoreboard_B1",env3);


    // ---- ENV B2 ----

    UVMComponent* agtB2 =
        Factory::instance().createComponent("Agent","Agent_B2",env4);

    UVMComponent* drvB2 =
        Factory::instance().createComponent("Driver","Driver_B2",agtB2);

    UVMComponent* monB2 =
        Factory::instance().createComponent("Monitor","Monitor_B2",agtB2);

    UVMComponent* covB2 =
        Factory::instance().createComponent("Coverage","Coverage_B2",agtB2);

    UVMComponent* scbB2 =
        Factory::instance().createComponent("Scoreboard","Scoreboard_B2",env4);



    //------------------------------------------------------
    // OBJECTS (NO jerarquía UVMComponent)
    //------------------------------------------------------

    UVMObject* seqA =
        Factory::instance().createObject("Sequence","Seq_A");

    UVMObject* seqItemA =
        Factory::instance().createObject("SequenceItem","SeqItem_A");

    UVMObject* bfmA =
        Factory::instance().createObject("BFMImpl","BFM_A");

    UVMObject* refA =
        Factory::instance().createObject("RefModelImpl","RefModel_A");



    /********************************************************
     *
     * COPY BASEFILE (PRIMERO TODO)
     *
     ********************************************************/

    top->copyBasefile();
    test1->copyBasefile();
    env1->copyBasefile();
    env2->copyBasefile();

    agtA1->copyBasefile();
    drvA1->copyBasefile();
    monA1->copyBasefile();
    covA1->copyBasefile();
    scbA1->copyBasefile();

    agtA2->copyBasefile();
    drvA2->copyBasefile();
    monA2->copyBasefile();
    covA2->copyBasefile();
    scbA2->copyBasefile();



    test2->copyBasefile();
    env3->copyBasefile();
    env4->copyBasefile();

    agtB1->copyBasefile();
    drvB1->copyBasefile();
    monB1->copyBasefile();
    covB1->copyBasefile();
    scbB1->copyBasefile();

    agtB2->copyBasefile();
    drvB2->copyBasefile();
    monB2->copyBasefile();
    covB2->copyBasefile();
    scbB2->copyBasefile();


    // Objects

    seqA->copyBasefile();
    seqItemA->copyBasefile();
    bfmA->copyBasefile();
    refA->copyBasefile();



    /********************************************************
     *
     * PRINT TREE
     *
     ********************************************************/

    top->printInfo();
    test1->printInfo();

    env1->printInfo();
    agtA1->printInfo();
    drvA1->printInfo();
    monA1->printInfo();
    covA1->printInfo();
    scbA1->printInfo();

    env2->printInfo();
    agtA2->printInfo();
    drvA2->printInfo();
    monA2->printInfo();
    covA2->printInfo();
    scbA2->printInfo();


    test2->printInfo();

    env3->printInfo();
    agtB1->printInfo();
    drvB1->printInfo();
    monB1->printInfo();
    covB1->printInfo();
    scbB1->printInfo();

    env4->printInfo();
    agtB2->printInfo();
    drvB2->printInfo();
    monB2->printInfo();
    covB2->printInfo();
    scbB2->printInfo();


    // Objects

    seqA->printInfo();
    seqItemA->printInfo();
    bfmA->printInfo();
    refA->printInfo();
}

