#ifndef UVM_OBJECT_H
#define UVM_OBJECT_H

#include <string>
#include <iostream>
#include <iomanip>

class UVMObject {

protected:
    std::string uvmenvProjectDir;
    std::string basefilePath;
    std::string name;
    std::string typeName;

public:
    UVMObject(const std::string& typeName, const std::string& name){
        this -> typeName = typeName;
        this -> name = name;
    }
    virtual ~UVMObject() = default;

    void printInfo(){
        std::cout << std::left 
            << "[" << std::setw(15) << typeName << "]"    // Column 1: Type
            << " ===>  "                                  // Fixed separator
            << std::setw(25) << name                      // Column 2: Name
            << std::endl;
    }
    void copyBasefile(){
        std::cout << "Copiar archivo base de [object] " << basefilePath << " a " << uvmenvProjectDir << std::endl;
    }

    // for printInfo
    std::string getName(){
        return this->name;
    }
};

#endif // UVM_OBJECT_H