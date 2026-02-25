#ifndef FACTORY_REGISTER_H
#define FACTORY_REGISTER_H

#include "Factory.h"

// =======================
// Component Register
// =======================

template<typename T>

class ComponentRegister {

public:
    ComponentRegister(const string& name){
        Factory::instance().registerComponent(
            name, [](){
                return new T();
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
    ObjectRegister(const string& name){
        Factory::instance().registerObject(
            name, [](){
                return new T();
            }
        );
    }
};



#endif // FACTORY_REGISTER_H

