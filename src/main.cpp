#include "headers/functions/utils.h"
#include "headers/functions/constants.h"
#include "headers/uvmenv_handling/general_handling/pre_project.h"
#include "headers/uvmenv_handling/general_handling/framework.h"
#include "headers/uvm_components/Agent.h"
#include "headers/VerilatorHandler.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>
using namespace std;

// NOTE: Include sudo apt install nlohmann-json3-dev on install script.



int main (int argc, char *argv[]) {
    cout << C_GREEN << "UVMEnv 2.0 - TESTING/DEVELOPING" << C_N << endl;
    activatePythonVenv();

    if(argc < 2) {
        showHelp();
        return 0;
    }

    string option = argv[1];
    
    ///// Framework handling /////
    if(option == "new") {
        // argv[2]: Project name.
        // argv[3]: Top module name.

        if(argv[2] == nullptr || argv[3] == nullptr){
            printError("Missing parameters");
            printInfo("Usage: uvmenv -n|--new <project name> <top module name>");
            exit(0);
        }

        createNewEnv(argv[2], argv[3]);
    } 
    else if(option == "search") {
        searchProjects();
    } 
    else if(option == "help") {
        showHelp();
    }

    ///// Project handling /////
    else if(option == "project"){
        if(!isUVMEnvProject()){
            printError("You need using a valid project to run this option.");
            return 1;
        }
        
        if(argv[2] == "view"){
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
    
    ///// Component handling /////
    else if(option == "component"){
        if(!isUVMEnvProject()){
            printError("You need using a valid project to run this option.");
            return 1;
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
            printError("Unknown project option: " + string(argv[2]));
            return 2;
        }
        
    }

    else if(option == "test") {
        //cout << getBasesRepresentDir() << endl;
        //cout << getPythonVersion() << endl;
        // Agent agent;
        // agent.display();
        // cout << agent.to_string() << endl;

        // vector<string> srcFiles = getFileNamesInDirectory("/home/manbenit/Github/cv");
        // for(auto f : srcFiles)
        //     cout << f << endl;

        cout << execCmdReturn(getScriptsPath() + "/python_control.sh getPythonVersion") << endl;

    }

    else {
        printError("Unknown option: " + option);
        return 2;
    }

    return 0;
}

