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

UVMComponent* Factory::createComponent(const string& typeName, const string& instanceName, const string& parent){
    auto it = components.find(typeName);

    if(it == components.end()){
        throw runtime_error("Factory ERROR: Component not registered -> " + typeName);
    }

    // "second" returns the value of pair (name, lambda)
    return it->second(instanceName,parent);
}

UVMObject* Factory::createObject(const string& typeName, const string& instanceName){
    auto it = objects.find(typeName);

    if(it == objects.end()){
        throw runtime_error("Factory ERROR: Object not registered -> " + typeName);
    }

    // "second" returns the value of pair (name, lambda)
    return it->second(instanceName);
}

