#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include <functional>
#include <string>

class UVMComponent;
class UVMObject;

class Factory {

public:
    // Factory templates (creator types)
    using ComponentCreator = std::function<UVMComponent*(const std::string&,const std::string&, UVMComponent*)>;
    using ObjectCreator = std::function<UVMObject*(const std::string&, const std::string&)>;

    // Singleton
    static Factory& instance();


    // Registration
    void registerComponent(const std::string& name, ComponentCreator creator);
    void registerObject(const std::string& name, ObjectCreator creator);
    
    // Creation
    UVMComponent* createComponent(const std::string& typeName, const std::string& instanceName, UVMComponent* parent);
    UVMObject* createObject(const std::string& typeName, const std::string& instanceName);

private:
    Factory() = default;
    std::unordered_map<std::string, ComponentCreator> components;
    std::unordered_map<std::string, ObjectCreator> objects;
};

#endif // FACTORY_H

