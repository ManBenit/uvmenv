#include "../../../headers/uvmenv_handling/component_handling/edit_component.h"

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>
#include <vector>
#include <vector>
#include <iostream>

#include "../../../headers/uvmenv_pseudo/components/Test.h"
#include "../../../headers/uvmenv_pseudo/components/Environment.h"
#include "../../../headers/uvmenv_pseudo/objects/Sequence.h"
#include "../../../headers/uvmenv_pseudo/objects/BFMImpl.h"
#include "../../../headers/uvmenv_pseudo/objects/SequenceItem.h"
#include "../../../headers/uvmenv_pseudo/objects/RefModelImpl.h"

#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
using namespace std;


void editBFM(const string& name){
    BFMImpl* bfm = (BFMImpl*) Factory::instance().createObject("BFMImpl", name);
    bfm->editFile(name);
}

// void editTest(const string& name){
//     string formatedName = "Test" + toPascalCase(name);
//     bool alreadyExists = false;

//     for(const auto& e: treeListTest()){
//         if(e == formatedName){
//             alreadyExists = true;
//             break;
//         }
//     }

//     if(alreadyExists){
//         printWarning( "The test " + formatedName + " already exists. Please choose another name." );
//         return;
//     }

//     Test* test = (Test*) Factory::instance().editComponent("Test", formatedName, &Top::instance());
//     test->setName(formatedName);
//     test->copyBaseFile();

//     // Create default directories for the test
//     filesystem::edit_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Misces");
//     filesystem::copy(
//         REPORT_FILEBASE,
//         TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Misces" + PATH_SEP + "UVMEnvReport.py"
//     );
//     filesystem::copy(
//         SIGREADER_FILEBASE,
//         TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Misces" + PATH_SEP + "SignalsReader.py"
//     );
//     filesystem::edit_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Envmnt");
//     filesystem::edit_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Seqnce");
//     filesystem::edit_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "SeqItm");

//     treeAddTest(formatedName);
// }

// void editSequence(const string& name, const string& testName){
//     string formatedName = "Seq" + toPascalCase(name);
//     bool alreadyExists = false;

//     for(const auto& e: treeListSequences(testName)){
//         if(e == formatedName){
//             alreadyExists = true;
//             break;
//         }
//     }

//     if(alreadyExists){
//         printWarning( "The sequence " + formatedName + " already exists. Please choose another name." );
//         return;
//     }

//     Sequence* sequence = (Sequence*) Factory::instance().editObject("Sequence", formatedName);
//     sequence->setName(formatedName);
//     sequence->setTestContainer(testName);
//     sequence->copyBaseFile();

//     treeAddSequences(formatedName, testName);
// }

// void editSeqitem(const string& name, const string& testName){
//     string formatedName = "Sit" + toPascalCase(name);
//     bool alreadyExists = false;

//     for(const auto& e: treeListSeqitem(testName)){
//         if(e == formatedName){
//             alreadyExists = true;
//             break;
//         }
//     }

//     if(alreadyExists){
//         printWarning( "The sequence item " + formatedName + " already exists. Please choose another name." );
//         return;
//     }

//     SequenceItem* seqitem = (SequenceItem*) Factory::instance().editObject("SequenceItem", formatedName);
//     seqitem->setName(formatedName);
//     seqitem->setTestContainer(testName);
//     seqitem->copyBaseFile();

//     treeAddSeqitem(formatedName, testName);
// }

// void editEnvironmentOnTest(const string& name, const string& testName){
//     string formatedName = "Env" + toPascalCase(name);
//     string envPath = TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Envmnt" + PATH_SEP + formatedName;
//     bool alreadyExists = false;

//     for(const auto& e: treeListEnvironments(testName)){
//         if(e == formatedName){
//             alreadyExists = true;
//             break;
//         }
//     }

//     if(alreadyExists){
//         printWarning( "The environment " + formatedName + " already exists. Please choose another name." );
//         return;
//     }


//     filesystem::edit_directory(envPath);
//     filesystem::edit_directory(envPath + PATH_SEP + "Agents");
//     filesystem::edit_directory(envPath + PATH_SEP + "Scorbd");
//     filesystem::edit_directories(envPath + PATH_SEP + "RefMdl" + PATH_SEP + "_impl");
//     filesystem::copy(
//         BASES_COMPONENT_DIR + PATH_SEP + "RefmodelBase.py",
//         envPath + PATH_SEP + "RefMdl" + PATH_SEP + "RefModel.py"
//     );

//     Environment* env    = (Environment*) Factory::instance().editComponent("Environment", formatedName, nullptr);
//     env->setName(formatedName);
//     env->setTestContainer(testName);
//     env->copyBaseFile();

//     treeAddEnvironment(formatedName, testName);
// }

// void editEnvironmentOnEnv(const string& name, const string& testName, const string& envParentName){
//     cout << "Comming soon..." << endl;
// }

// void editRefModel(const string& name, const string& testName, const string& envName){
//     string formatedName = "Ref" + toPascalCase(name);
//     bool alreadyExists = false;

//     for(const auto& e: treeListRefmodel(testName, envName)){
//         if(e == formatedName){
//             alreadyExists = true;
//             break;
//         }
//     }

//     if(alreadyExists){
//         printWarning( "The reference model " + formatedName + " already exists. Please choose another name." );
//         return;
//     }

//     RefModelImpl* refmodel = (RefModelImpl*) Factory::instance().editObject("RefModelImpl", formatedName);
//     refmodel->setName(formatedName);
//     refmodel->setTestContainer(testName);
//     refmodel->setEnvContainer(envName);
//     refmodel->copyBaseFile();

//     treeAddRefmodel(formatedName, testName, envName);
// }

// void editAgent(const string& name, const string& testName, const string& envName, const string& type){
//     // TODO: Use "type" to edit specific kind of agents (active, passive or reactive)
//     string formatedName = "agnt_" + toSnakeCase(name);
//     bool alreadyExists = false;

//     for(const auto& e: treeListAgents(testName, envName)){
//         if(e == formatedName){
//             alreadyExists = true;
//             break;
//         }
//     }

//     if(alreadyExists){
//         printWarning( "The sequence item " + formatedName + " already exists. Please choose another name." );
//         return;
//     }

//     Agent* agent = (Agent*) Factory::instance().editComponent("Agent", formatedName, nullptr);
//     agent->setName(formatedName);
//     agent->setTestContainer(testName);
//     agent->setEnvContainer(envName);
//     agent->setAgentType(type);
//     agent->copyBaseFile();

//     treeAddAgent(formatedName, testName, envName);
// }

// void editScoreboard(const string& name, const string& testName, const string& envName){
//     string formatedName = "Scb" + toPascalCase(name);
//     bool alreadyExists = false;

//     for(const auto& e: treeListScoreboards(testName, envName)){
//         if(e == formatedName){
//             alreadyExists = true;
//             break;
//         }
//     }

//     if(alreadyExists){
//         printWarning( "The scoreboard " + formatedName + " already exists. Please choose another name." );
//         return;
//     }

//     Scoreboard* scoreboard = (Scoreboard*) Factory::instance().editComponent("Scoreboard", formatedName, nullptr);
//     scoreboard->setName(formatedName);
//     scoreboard->setTestContainer(testName);
//     scoreboard->setEnvContainer(envName);
//     scoreboard->copyBaseFile();

//     treeAddScoreboard(formatedName, testName, envName);
// }




