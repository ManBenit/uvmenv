#ifndef TEST_H
#define TEST_H

#include "Environment.h"
using namespace std;


class Test : public UVMComponent {
private:
    vector<Environment*> environments;

public:
    void printInfo() override {
        cout << "[Test] " << name << ", Parent: " << parent << endl;
    }

    void addEnvironment(Environment* e) { environments.push_back(e); }
    vector<Environment*> getEnvironments() { return environments; }
};


#endif // TEST_H


