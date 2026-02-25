#ifndef UVM_OBJECT_H
#define UVM_OBJECT_H

#include <string>
#include <iostream>
using namespace std;

class UVMObject {

protected:
    string uvmenvProjectDir;
    string basefilePath;
    string name;

public:
    virtual ~UVMObject() = default;

    virtual void setName(const string& name){
        this->name = name;
    }

    virtual void printInfo(){}
    virtual void copyBasefile(){}

};

#endif // UVM_OBJECT_H