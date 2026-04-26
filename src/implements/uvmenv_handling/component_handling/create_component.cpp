#ifndef CREATE
#define CREATE


#include <string>
#include <filesystem>
#include <vector>
#include <vector>
#include <iostream>

#include "../../../headers/uvmenv_preudo/Factory.h"

#include "../../../headers/uvmenv_preudo/components/Top.h"
#include "../../../headers/uvmenv_preudo/components/Test.h"
#include "../../../headers/uvmenv_preudo/components/Environment.h"

#include "../../../headers/uvmenv_preudo/objects/Sequence.h"
#include "../../../headers/uvmenv_preudo/objects/SequenceItem.h"
#include "../../../headers/uvmenv_preudo/objects/RefModelImpl.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/ptree_handling.h"
#include "../../../headers/uvmenv_handling/component_handling/create_component.h"
using namespace std;

vector<string> options = {"test", "env", "agent", "seqitem", "seqce", "scorebd", "refmod", "bfm"};
string ptree_file = PROJECT_DIR + PATH_SEP + "ptree.yml";


void createUVMEnvComponent(const string& type){
    if(!isInOptions(type, &options)){
        cout << type << " is not a valid component reference for creation" << endl;
    }


}

void listUVMEnvComponents(const string& type){
    vector<string> listOptions = {"rtlsig", "rtlmod"};
    listOptions.insert(listOptions.end(), options.begin(), options.end());

    if(!isInOptions(type, &listOptions)){
        cout << type << " is not a valid component reference for listing" << endl;
    }
}

void editUVMEnvComponents(const string& type){
    vector<string> editOptions = {"top", "config", "util", "path"};
    editOptions.insert(editOptions.end(), options.begin(), options.end());

    if(!isInOptions(type, &editOptions)){
        cout << type << " is not a valid component reference for edition" << endl;
    }
}

void deleteUVMEnvComponent(const string& type){
    if(!isInOptions(type, &options)){
        cout << type << " is not a valid component reference for deletion" << endl;
    }
}


void createTest(const string& name){
    string formatedName = "Test" + toPascalCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListTest()){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The test " + formatedName + " already exists. Please choose another name." );
        return;
    }

    Test* test = (Test*) Factory::instance().createComponent("Test", formatedName, &Top::instance());
    test->setName(formatedName);
    test->copyBaseFile();

    // Create default directories for the test
    filesystem::create_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Misces");
    filesystem::copy(
        REPORT_FILEBASE,
        TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Misces" + PATH_SEP + "UVMEnvReport.py"
    );
    filesystem::create_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Envmnt");
    filesystem::create_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Seqnce");
    filesystem::create_directory(TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "SeqItm");

    treeAddTest(formatedName);
}

void createSequence(const string& name, const string& testName){
    string formatedName = "Seq" + toPascalCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListSequences(testName)){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The sequence " + formatedName + " already exists. Please choose another name." );
        return;
    }

    Sequence* sequence = (Sequence*) Factory::instance().createObject("Sequence", formatedName);
    sequence->setName(formatedName);
    sequence->setTestContainer(testName);
    sequence->copyBaseFile();

    treeAddSequences(formatedName, testName);
}

void createSeqitem(const string& name, const string& testName){
    string formatedName = "sit_" + toSnakeCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListSeqitem(testName)){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The sequence item " + formatedName + " already exists. Please choose another name." );
        return;
    }

    SequenceItem* seqitem = (SequenceItem*) Factory::instance().createObject("SequenceItem", formatedName);
    seqitem->setName(formatedName);
    seqitem->setTestContainer(testName);
    seqitem->copyBaseFile();

    treeAddSeqitem(formatedName, testName);
}

void createEnvironmentOnTest(const string& name, const string& testName){
    string formatedName = "Env" + toPascalCase(name);
    string envPath = TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Envmnt" + PATH_SEP + formatedName;
    bool alreadyExists = false;

    for(const auto& e: treeListEnvironments(testName)){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The environment " + formatedName + " already exists. Please choose another name." );
        return;
    }


    filesystem::create_directory(envPath);
    filesystem::create_directory(envPath + PATH_SEP + "Agents");
    filesystem::create_directory(envPath + PATH_SEP + "Scorbd");
    filesystem::create_directories(envPath + PATH_SEP + "RefMdl" + PATH_SEP + "_impl");
    filesystem::copy(
        BASES_COMPONENT_DIR + PATH_SEP + "RefmodelBase.py",
        envPath + PATH_SEP + "RefMdl" + PATH_SEP + "RefModel.py"
    );

    Environment* env    = (Environment*) Factory::instance().createComponent("Environment", formatedName, nullptr);
    env->setName(formatedName);
    env->setTestContainer(testName);
    env->copyBaseFile();

    treeAddEnvironment(formatedName, testName);
}

void createEnvironmentOnEnv(const string& name, const string& envParentName, const string& testName){
    cout << "Comming soon..." << endl;
}

void createRefModel(const string& name, const string& envName, const string& testName){
    string formatedName = "Ref" + toPascalCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListRefmodel(testName, envName)){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The reference model " + formatedName + " already exists. Please choose another name." );
        return;
    }

    RefModelImpl* refmodel = (RefModelImpl*) Factory::instance().createObject("RefModelImpl", formatedName);
    refmodel->setName(formatedName);
    refmodel->setTestContainer(testName);
    refmodel->setEnvContainer(envName);
    refmodel->copyBaseFile();

    treeAddRefmodel(formatedName, testName, envName);
}

void createAgent(const string& name, const string& envName, const string& testName){
    string formatedName = "agnt_" + toSnakeCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListAgents(testName, envName)){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The sequence item " + formatedName + " already exists. Please choose another name." );
        return;
    }

    Agent* agent = (Agent*) Factory::instance().createComponent("Agent", formatedName, nullptr);
    agent->setName(formatedName);
    agent->setTestContainer(testName);
    agent->setEnvContainer(envName);
    agent->copyBaseFile();

    treeAddAgent(formatedName, testName, envName);
}

void createScoreboard(const string& name, const string& envName, const string& testName){
    string formatedName = "Scb" + toPascalCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListScoreboards(testName, envName)){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The scoreboard " + formatedName + " already exists. Please choose another name." );
        return;
    }

    Scoreboard* scoreboard = (Scoreboard*) Factory::instance().createComponent("Scoreboard", formatedName, nullptr);
    scoreboard->setName(formatedName);
    scoreboard->setTestContainer(testName);
    scoreboard->setEnvContainer(envName);
    scoreboard->copyBaseFile();

    treeAddScoreboard(formatedName, testName, envName);
}

void createBFM(const string& name){
    string formatedName = "BFM" + toPascalCase(name);
    bool alreadyExists = false;

    for(const auto& e: treeListInterface()){
        if(e == formatedName){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        printWarning( "The interface " + formatedName + " already exists. Please choose another name." );
        return;
    }

    filesystem::copy(
        BASES_COMPONENT_DIR + PATH_SEP + "RefmodelImplBase.py",
        BFM_DIR + PATH_SEP + "_impl" + PATH_SEP + formatedName+".py"
    );

    treeAddInterface(formatedName);
}

#endif




