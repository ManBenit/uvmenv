// #include "../../headers/uvmenv_preudo/UVMEnvFactory.h"

// unordered_map<string, UVMEnvFactory::ComponentCreator>
// UVMEnvFactory::componentRegistry;

// unordered_map<string, UVMEnvFactory::ObjectCreator>
// UVMEnvFactory::objectRegistry;

// void UVMEnvFactory::registerDefaults(){
//     UVMEnvFactory::componentRegistry["agent"] = []() { return new Agent(); };
//     UVMEnvFactory::componentRegistry["driver"] = []() { return new Driver(); };
//     UVMEnvFactory::componentRegistry["monitor"] = []() { return new Monitor(); };
//     UVMEnvFactory::componentRegistry["environment"] = []() { return new Environment(); };
//     UVMEnvFactory::componentRegistry["test"] = []() { return new Test(); };
//     UVMEnvFactory::componentRegistry["coverage"] = []() { return new Coverage(); };
//     UVMEnvFactory::componentRegistry["scoreboard"] = []() { return new Scoreboard(); };

//     UVMEnvFactory::objectRegistry["sequence"] = []() { return new Sequence(); };
//     UVMEnvFactory::objectRegistry["sequence_item"] = []() { return new SequenceItem(); };
//     UVMEnvFactory::objectRegistry["bfm_impl"] = []() { return new BFMImpl(); };
//     UVMEnvFactory::objectRegistry["refmodel_impl"] = []() { return new RefModelImpl(); };
// }