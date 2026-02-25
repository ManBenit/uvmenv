#ifndef UVM_COMPONENT_H
#define UVM_COMPONENT_H

#include <string>
#include <iostream>

class UVMComponent {

protected:
    std::string uvmenvProjectDir;
    std::string basefilePath;
    UVMComponent* parent;
    std::string name;

public:
    UVMComponent(const std::string& name, UVMComponent* parent){
        this->name = name;
        this->parent = parent;
    }

    virtual ~UVMComponent() = default;
    virtual void printInfo(){}
    void copyBasefile(){
        std::cout << "Copiar archivo base de [component] " << basefilePath << "a " << uvmenvProjectDir << std::endl;
    }

    // for printInfo
    std::string getName(){
        return this->name;
    }
};


#endif // UVM_COMPONENT_H

