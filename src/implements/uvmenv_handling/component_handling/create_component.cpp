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

#include "../../../headers/uvmenv_preudo/objects/Sequence.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/ptree_handling.h"
#include "../../../headers/uvmenv_handling/component_handling/create_component.h"
using namespace std;

vector<string> options = {"test", "env", "agent", "seqitem", "seqce", "scorebd", "refmod", "bfm"};
string ptree_file = PROJECT_DIR + PATH_SEP + "ptree.yml";


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
    string pascalName = "Test" + toPascalCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListTest()){
        if(e == pascalName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The test " + pascalName + " already exists. Please choose another name." );
        return;
    }

    Test* test = (Test*) Factory::instance().createComponent("Test", pascalName, &Top::instance());
    test->setName(pascalName);
    test->copyBaseFile();

    // Create default directories for the test
    filesystem::create_directory(TBENCH_DIR + PATH_SEP + pascalName + PATH_SEP + "Envmnt");
    filesystem::create_directory(TBENCH_DIR + PATH_SEP + pascalName + PATH_SEP + "Seqnce");
    filesystem::create_directory(TBENCH_DIR + PATH_SEP + pascalName + PATH_SEP + "Seqitm");

    treeAddTest(pascalName);
}

void createSequence(const string& name, const string& testName){
    string pascalName = "Seq" + toPascalCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListSequences(testName)){
        if(e == pascalName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The sequence " + pascalName + " already exists. Please choose another name." );
        return;
    }

    Sequence* sequence = (Sequence*) Factory::instance().createObject("Sequence", pascalName);
    sequence->setName(pascalName);
    sequence->setTestContainer(testName);
    sequence->copyBaseFile();

    treeAddSequences(pascalName, testName);
}


void createEnvironment(const string& name, Test* test){
    string pascalName = "Env" + toPascalCase(name);
    Environment* env    = (Environment*) Factory::instance().createComponent("Environment", pascalName, test);
    //env->setName(pascalName);
    env->copyBaseFile();
}
void createEnvironment(const string& name, Environment* env){
    string pascalName = "Env" + toPascalCase(name);
    Environment* subEnv = (Environment*) Factory::instance().createComponent("Environment", pascalName, env);
    //subEnv->setName("Env" + toPascalCase(name));
    subEnv->copyBaseFile();
}

// name: with snake_case
void createAgent(const string& name, const string& attr, const string& module, Environment* env){
    UVMComponent* agent = Factory::instance().createComponent("Agent", name, env);
    agent->create();

    if (name == "" || attr == "" || module == "") {
        cout << "Missing parameters for creating an Agent" << endl; 
        cout << "Usage: uvmenv create component agent <attr> <name> <module>" << endl;
    //uvmenv -c|--create agnt <attr> <agent_name> <module>
        exit(3);
    }

        
}


#endif

