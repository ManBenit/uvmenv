#ifndef UVM_OBJECT_H
#define UVM_OBJECT_H

#include <string>
#include <iostream>

class UVMObject {

protected:
    std::string uvmenvProjectDir;
    std::string basefilePath;
    std::string name;

public:
    UVMObject(const std::string& name, UVMComponent* parent){
        this->name = name;
    }
    virtual ~UVMObject() = default;
    virtual void printInfo(){}
    void copyBasefile(){
        std::cout << "Copiar archivo base de [object] " << basefilePath << "a " << uvmenvProjectDir << std::endl;
    }

    // for printInfo
    std::string getName(){
        return this->name;
    }
};

#endif // UVM_OBJECT_H