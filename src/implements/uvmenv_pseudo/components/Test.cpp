#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Test.h"
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
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
    filesystem::create_directory(uvmenvProjectDir + PATH_SEP + name);
    filesystem::copy(
        basefilePath, 
        uvmenvProjectDir + PATH_SEP + name + PATH_SEP + PYMODULE
    );
    cout << "Copiar base del Top" << endl;
}


// private
ComponentRegister<Test> Test::reg("Test");


