#ifndef TEST_H
#define TEST_H

#include "Environment.h"
#include "../FactoryRegister.h"
#include "../UVMComponent.h"
using namespace std;


class Test : public UVMComponent {
private:
    vector<Environment*> environments;

public:
    virtual ~Test() = default;
    void addEnvironment(Environment* e);
    vector<Environment*> getEnvironments();


    void printInfo() override;
    void copyBasefile() override;

private:
    // auto registration
    static ComponentRegister<Test> reg;
};


#endif // TEST_H


