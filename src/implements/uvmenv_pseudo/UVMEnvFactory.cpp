#include "../../headers/uvmenv_preudo/UVMEnvFactory.h"


void UVMEnvFactory::registerDefaults(){
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

