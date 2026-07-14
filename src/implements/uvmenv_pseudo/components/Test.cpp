#include "../../../headers/uvmenv_pseudo/components/Test.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <yaml-cpp/yaml.h>
using namespace std;


void Test::addEnvironment(Environment* e) { 
    environments.push_back(e); 
}

vector<Environment*> Test::getEnvironments() { 
    return environments; 
}

void Test::setName(const string& name){
    this->name = name;
}

void Test::editFile(const string& name){
    const string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDir;

    if(!filesystem::exists(uvmenvProjectDir)){
        printError("Does not exist " + name);
        exit(5);
    }

    int sysResult = system(file.c_str());
    if (sysResult== 0) {
        printInfo("Finished edition of " + name);
    } else {
        printError( "Something went wrong while editing " + name + ". Returned code " + to_string(sysResult) );
    }
}


// @Override
void Test::copyBaseFile(){
    uvmenvProjectDir = joinStr({TBENCH_DIR, name, PYMODULE}, PATH_SEP);

    
    filesystem::create_directory(uvmenvProjectDir + PATH_SEP + name);

    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    // Write project file
    ofstream outFile(uvmenvProjectDir);
    outFile << content;
    outFile.close();
}


// private
ComponentRegister<Test> Test::reg("Test");


