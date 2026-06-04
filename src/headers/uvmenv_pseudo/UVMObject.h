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

    virtual void copyBaseFile(){}

    friend std::ostream& operator<<(std::ostream& os, const UVMObject& obj) {
        os << std::left 
            << "[" << std::setw(15) << obj.typeName << "]"
            << " ===>  " 
            << std::setw(25) << obj.name;
            //<< (obj.parent != nullptr ? obj.parent->name : "N/A");
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const UVMObject* obj) {
        if (obj == nullptr) return os << "NULL";
        return os << *obj; // Llama a la sobrecarga de arriba
    }
};

#endif // UVM_OBJECT_H