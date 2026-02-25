#ifndef FACTORY_REGISTER_H
#define FACTORY_REGISTER_H

#include "Factory.h"

class UVMComponent;

// =======================
// Component Register
// =======================

template<typename T>

class ComponentRegister {

public:
    ComponentRegister(const std::string& typeName){
        Factory::instance().registerComponent(
            typeName, 
            [](const std::string& name, UVMComponent* parent){
                return new T(name, parent);
            }
        );
    }
};


// =======================
// Object Register
// =======================

template<typename T>

class ObjectRegister {

public:
    ObjectRegister(const std::string& typeName){
        Factory::instance().registerObject(
            typeName, 
            [](const std::string& name){
                return new T(name);
            }
        );
    }
};



#endif // FACTORY_REGISTER_H

