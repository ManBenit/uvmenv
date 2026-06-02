#include "../../../headers/uvmenv_handling/component_handling/create_component.h"

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>
#include <vector>
#include <vector>
#include <iostream>

#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include "../../../headers/uvmenv_preudo/Factory.h"

#include "../../../headers/uvmenv_preudo/components/Top.h"
#include "../../../headers/uvmenv_preudo/components/Test.h"
#include "../../../headers/uvmenv_preudo/components/Environment.h"

#include "../../../headers/uvmenv_preudo/objects/Sequence.h"
#include "../../../headers/uvmenv_preudo/objects/SequenceItem.h"
#include "../../../headers/uvmenv_preudo/objects/RefModelImpl.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/component_handling/ptree_handling.h"
using namespace std;

vector<string> options = {"test", "env", "agent", "seqitem", "seqce", "scorebd", "refmod", "bfm"};
string ptree_file = PROJECT_DIR + PATH_SEP + "ptree.yml";


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


    
    ifstream baseFile(BASES_COMPONENT_DIR + PATH_SEP + "BFMImplBase.py");
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Change class name
    content = regex_replace(content, regex("CLASS_NAME"), "PruebaCambio");
    content = regex_replace(content, regex("GET_INS|GET_OUTS"), doTabs(3)+"a: \"99\""); //*** */
    
    for (const auto& grupo_senales : getDUTSignals('n')) {
        // Ahora iteramos sobre cada Signal individual dentro de ese grupo
        for (const auto& s : grupo_senales) {
            // En C++ accedemos con s.type, s.size y s.name (NO con ["string"])
            print(s.type + "[" + to_string(s.size) + " bit]: " + s.name);
        }
    }
    //sed -r "s|CLASS_NAME|$1|g" $BFM_IMPL_FILEBASE > $BFMIMPL_DIR/tmp1.py  

    // ## Change set method (parameters and inits)

    // sed -r "s|PARAMETERS|$parameters_of_set|g" $BFMIMPL_DIR/tmp1.py > $BFMIMPL_DIR/tmp2.py  
    // sed -r "s|INIT_VALUES|$init_values_on_set|g" $BFMIMPL_DIR/tmp2.py > $BFMIMPL_DIR/tmp3.py  
    // rm $BFMIMPL_DIR/tmp1.py
    // rm $BFMIMPL_DIR/tmp2.py

    // ## Change get method (ins and outs sets)
    // sed -r "s|GET_INS|$inputs_of_get|g" $BFMIMPL_DIR/tmp3.py > $BFMIMPL_DIR/tmp2.py  
    // sed -r "s|GET_OUTS|$outputs_of_get|g" $BFMIMPL_DIR/tmp2.py > destPath + formatedName+".py" 
    // rm $BFMIMPL_DIR/tmp3.py
    // rm $BFMIMPL_DIR/tmp2.py

    ofstream bfmImplFile(BFM_DIR + PATH_SEP + "_impl" + PATH_SEP + formatedName+".py");
    bfmImplFile << content;



    treeAddInterface(formatedName);
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

void createEnvironmentOnEnv(const string& name, const string& testName, const string& envParentName){
    cout << "Comming soon..." << endl;
}

void createRefModel(const string& name, const string& testName, const string& envName){
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

void createAgent(const string& name, const string& testName, const string& envName){
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

void createScoreboard(const string& name, const string& testName, const string& envName){
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




