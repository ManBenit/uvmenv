#include "../../../headers/uvmenv_preudo/components/Test.h"


void Test::addEnvironment(Environment* e) { 
    environments.push_back(e); 
}

vector<Environment*> Test::getEnvironments() { 
    return environments; 
}



// @Override
void Test::printInfo() {
    cout << "[Test] " << name << ", Parent: " << parent << endl;
}

void Test::copyBasefile() {
    cout << "print base file of Test" << endl;
}