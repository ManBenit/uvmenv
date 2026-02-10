#include "headers/functions/utils.h"
#include "headers/functions/constants.h"
#include "headers/functions/env_handling.h"
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
    if(option == "--new" || option == "-n") {
        // argv[2]: Project name.
        // argv[3]: Top module name.

        if(argv[2] == nullptr || argv[3] == nullptr){
            printError("Missing parameters");
            printInfo("Usage: uvmenv -n|--new <project name> <top module name>");
            exit(0);
        }

        createNewEnv(argv[2], argv[3]);
    } 
    else if(option == "--search" || option == "-s") {
        searchProjects();
    } 
    else if(option == "--help" || option == "-h") {
        showHelp();
    }
    else if(option == "--init" || option == "-i") {
        
    }
    else if(option == "--view" || option == "-v") {
        if(!isUVMEnvProject()){
            printError("You need using a valid project to run this option.");
            exit(1);
        }

        execCmdSimple(getScript("sys_commands") + "viewTreeProject");
    }
    else if(option == "run") {
        
    }
    else if(option == "wave") {
        if(!isUVMEnvProject()){
            printError("You need using a valid project to run this option.");
            exit(1);
        }

        execCmdSimple(getScriptsPath() + "/sys_commands.sh runGTKWave");
    }
    else if(option == "report") {
        if(!isUVMEnvProject()){
            printError("You need using a valid project to run this option.");
            exit(1);
        }

        execCmdSimple(getScriptsPath() + "/sys_commands.sh viewReport");
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

    ///// Component handling /////
    else if(option == "--create" || option == "-c") {
        
    }
    else if(option == "--list" || option == "-l") {
        
    }
    else if(option == "--edit" || option == "-e") {
        
    }
    else if(option == "--delete" || option == "-d") {
        
    }
    else {
        printError("Unknown option: " + option);
        return 2;
    }

    return 0;
}

