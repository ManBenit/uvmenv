#ifndef TEST_H
#define TEST_H

#include "Environment.h"
#include "../FactoryRegister.h"
#include "../UVMComponent.h"


class Test : public UVMComponent {
private:
    vector<Environment*> environments;

public:
    Test(const std::string& name, UVMComponent* parent): UVMComponent(name, parent){
        basefilePath = "sdfsdfdsf";
        uvmenvProjectDir = "43tf34f34f";
    }
    virtual ~Test() = default;
    void addEnvironment(Environment* e);
    vector<Environment*> getEnvironments();


    void printInfo() override;

private:
    // auto registration
    static ComponentRegister<Test> reg;
};


#endif // TEST_H


