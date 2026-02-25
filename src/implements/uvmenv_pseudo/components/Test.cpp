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
void Test::printInfo() {
    cout << "[Test] " << name << ", Parent: " << parent->getName() << endl;
}


// private
ComponentRegister<Test> Test::reg("Test");

