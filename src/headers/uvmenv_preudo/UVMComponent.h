#ifndef UVM_COMPONENT_H
#define UVM_COMPONENT_H

#include <string>
#include <iostream>
#include <iomanip>

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

    virtual void copyBaseFile(){}
    virtual void create(){}
    virtual void edit(){}
    virtual void list(){}
    virtual void remove(){}

    friend std::ostream& operator<<(std::ostream& os, const UVMComponent& obj) {
        os << std::left 
            << "[" << std::setw(15) << obj.typeName << "]"
            << " ===>  " 
            << std::setw(25) << obj.name
            << (obj.parent != nullptr ? obj.parent->name : "N/A");
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const UVMComponent* obj) {
        if (obj == nullptr) return os << "NULL";
        return os << *obj; // Llama a la sobrecarga de arriba
    }
};


#endif // UVM_COMPONENT_H



