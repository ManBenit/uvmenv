#include "../../../headers/uvmenv_pseudo/components/Test.h"

#include "../../../headers/functions/utils.h"

#include <iostream>
#include <regex>
#include <fstream>
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


// @Override
void Test::copyBaseFile(){
    filesystem::create_directory(uvmenvProjectDir + PATH_SEP + name);

    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    // Write project file
    ofstream testFile(joinStr({uvmenvProjectDir, name, PYMODULE}, PATH_SEP));
    testFile << content;
}


// private
ComponentRegister<Test> Test::reg("Test");


