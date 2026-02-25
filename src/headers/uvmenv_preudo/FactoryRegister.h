#ifndef FACTORY_REGISTER_H
#define FACTORY_REGISTER_H

#include "Factory.h"

// =======================
// Component Register
// =======================

template<typename T>

class ComponentRegister {

public:
    ComponentRegister(const string& typeName){
        Factory::instance().registerComponent(
            typeName, 
            [](const string& name, string& parent){
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
    ObjectRegister(const string& typeName){
        Factory::instance().registerObject(
            typeName, 
            [](const string& name){
                return new T(name);
            }
        );
    }
};



#endif // FACTORY_REGISTER_H

