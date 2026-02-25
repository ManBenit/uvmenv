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
    std::string typeName;

public:
    UVMComponent(const std::string& typeName, const std::string& name, UVMComponent* parent){
        this -> typeName = typeName; 
        this -> name = name;
        this -> parent = parent;
    }
    virtual ~UVMComponent() = default;

    void printInfo(){
        std::cout << "[" << typeName << "] ->\t" << name << "; Parent: " << (parent != nullptr ? parent->name : "N/A") << std::endl;
    }
    void copyBasefile(){
        std::cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << std::endl;
    }
};


#endif // UVM_COMPONENT_H

