#include "../../headers/uvmenv_preudo/Factory.h"

Factory& Factory::instance(){
    static Factory inst;
    return inst;
}

void Factory::registerComponent(const string& name, ComponentCreator creator){
    components[name] = creator;
}

void Factory::registerObject(const string& name, ObjectCreator creator){
    objects[name] = creator;
}

UVMComponent* Factory::createComponent(const string& name){
    return components.at(name)();
}

UVMObject* Factory::createObject(const string& name){
    return objects.at(name)();
}

