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
    // Factory templates (creator types)
    using ComponentCreator = function<UVMComponent*(const string&, const string&)>;
    using ObjectCreator = function<UVMObject*(const string&)>;

    // Singleton
    static Factory& instance();


    // Registration
    void registerComponent(const string& name, ComponentCreator creator);
    void registerObject(const string& name, ObjectCreator creator);
    
    // Creation
    UVMComponent* createComponent(const string& typeName, const string& instanceName, const string& parent);
    UVMObject* createObject(const string& typeName, const string& instanceName);

private:
    unordered_map<string, ComponentCreator> components;
    unordered_map<string, ObjectCreator> objects;
};

#endif // FACTORY_H

