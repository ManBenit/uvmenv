#ifndef UVMENVFACTORY_H
#define UVMENVFACTORY_H

#include "components/Agent.h"
#include "components/Driver.h"
#include "components/Monitor.h"
#include "components/Coverage.h"
#include "components/Environment.h"
#include "components/Test.h"
#include "components/Scoreboard.h"
#include "objects/Sequence.h"
#include "objects/SequenceItem.h"
#include "objects/BFMImpl.h"
#include "objects/RefModelImpl.h"
using namespace std;

class UVMEnvFactory {
public:
    using ComponentCreator = function<UVMComponent*()>;
    using ObjectCreator = function<UVMObject*()>;
    
    static unordered_map<string, ComponentCreator> componentRegistry;
    static unordered_map<string, ObjectCreator> objectRegistry;

    // Register components and objects in the factory
    void registerDefaults(){
        componentRegistry["agent"] = []() { return new Agent(); };
        componentRegistry["driver"] = []() { return new Driver(); };
        componentRegistry["monitor"] = []() { return new Monitor(); };
        componentRegistry["environment"] = []() { return new Environment(); };
        componentRegistry["test"] = []() { return new Test(); };
        componentRegistry["coverage"] = []() { return new Coverage(); };
        componentRegistry["scoreboard"] = []() { return new Scoreboard(); };

        objectRegistry["sequence"] = []() { return new Sequence(); };
        objectRegistry["sequence_item"] = []() { return new SequenceItem(); };
        objectRegistry["bfm_impl"] = []() { return new BFMImpl(); };
        objectRegistry["refmodel_impl"] = []() { return new RefModelImpl(); };
    }
};


#endif // UVMENVFACTORY_H

