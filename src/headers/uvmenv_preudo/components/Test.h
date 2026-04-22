#ifndef TEST_H
#define TEST_H

#include "Environment.h"
#include "../FactoryRegister.h"
#include "../UVMComponent.h"

class Test : public UVMComponent {

private:
    vector<Environment*> environments;

public:
    Test(const std::string& typeName, const std::string& name, UVMComponent* parent): UVMComponent(typeName, name, parent){
        basefilePath = BASES_REPRESENT_DIR + PATH_SEP + "TestBase.py";
        uvmenvProjectDir = TBENCH_DIR;
    }
    virtual ~Test() = default;
    void addEnvironment(Environment* e);
    vector<Environment*> getEnvironments();

    void copyBaseFile() override;

    void setName(const std::string& name);
    void writeOnTree();

private:
    // auto registration
    static ComponentRegister<Test> reg;
    string name;
    
};


#endif // TEST_H


