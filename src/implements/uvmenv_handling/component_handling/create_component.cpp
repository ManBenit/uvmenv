#ifndef CREATE
#define CREATE


#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include "../../../headers/uvmenv_preudo/Factory.h"
#include "../../../headers/uvmenv_preudo/components/Top.h"
#include "../../../headers/uvmenv_preudo/components/Test.h"
#include "../../../headers/uvmenv_preudo/components/Environment.h"
#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/component_handling/create_component.h"
using namespace std;

void createUVMEnvComponent(const string& type){
    if(!isInOptions(type, &options)){
        cout << type << " is not a valid component reference for creation" << endl;
    }


}

void listUVMEnvComponents(const string& type){
    vector<string> listOptions = {"rtlsig", "rtlmod"};
    listOptions.insert(listOptions.end(), options.begin(), options.end());

    if(!isInOptions(type, &listOptions)){
        cout << type << " is not a valid component reference for listing" << endl;
    }
}

void editUVMEnvComponents(const string& type){
    vector<string> editOptions = {"top", "config", "util", "path"};
    editOptions.insert(editOptions.end(), options.begin(), options.end());

    if(!isInOptions(type, &editOptions)){
        cout << type << " is not a valid component reference for edition" << endl;
    }
}

void deleteUVMEnvComponent(const string& type){
    if(!isInOptions(type, &options)){
        cout << type << " is not a valid component reference for deletion" << endl;
    }
}




// name: with PascalCase
void createTest(const string& name){
    UVMComponent* test = Factory::instance().createComponent("Test", name, &Top::instance());
    test->copyBaseFile();

}

void createEnvironment(const string& name, Test* test){
    UVMComponent* env = Factory::instance().createComponent("Environment", name, test);
    
}
void createEnvironment(const string& name, Environment* env){
    UVMComponent* subEnv = Factory::instance().createComponent("Environment", name, env);
   
}

// name: with snake_case
void createAgent(const string& name, const string& attr, const string& module, Environment* env){
    UVMComponent* agent = Factory::instance().createComponent("Agent", name, env);
    
}


#endif

