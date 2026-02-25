#ifndef UVM_COMPONENT_H
#define UVM_COMPONENT_H

#include <string>
#include <iostream>
using namespace std;

class UVMComponent {

protected:
    const string uvmenvProjectDir;
    const string basefilePath;
    string parent;
    string name;

public:
    virtual ~UVMComponent() = default;

    virtual void setParent(const string& parent){
        this->parent = parent;
    }

    virtual void setName(const string& name){
        this->name = name;
    }

    virtual void printInfo(){}
    virtual void copyBasefile(){}
};


#endif // UVM_COMPONENT_H

