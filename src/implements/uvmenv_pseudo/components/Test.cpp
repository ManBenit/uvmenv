#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Test.h"
using namespace std;


void Test::addEnvironment(Environment* e) { 
    environments.push_back(e); 
}

vector<Environment*> Test::getEnvironments() { 
    return environments; 
}


// @Override
void Test::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Test> Test::reg("Test");


