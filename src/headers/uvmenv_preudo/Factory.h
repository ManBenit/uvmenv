#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include <functional>
#include "UVMComponent.h"
#include "UVMObject.h"
using namespace std;

//class UVMComponent;
//class UVMObject;

class Factory {

public:
    using ComponentCreator = function<UVMComponent*()>;
    using ObjectCreator = function<UVMObject*()>;

    // Singleton
    static Factory& instance();


    // Registration
    void registerComponent(const string& name, ComponentCreator creator);
    void registerObject(const string& name, ObjectCreator creator);
    
    // Creation
    UVMComponent* createComponent(const string& name);
    UVMObject* createObject(const string& name);

private:
    unordered_map<string, ComponentCreator> components;
    unordered_map<string, ObjectCreator> objects;
};

#endif // FACTORY_H

