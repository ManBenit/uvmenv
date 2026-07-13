#include "../../../headers/uvmenv_handling/component_handling/create_component.h"

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>
#include <vector>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include "../../../headers/uvmenv_pseudo/Factory.h"

#include "../../../headers/uvmenv_pseudo/components/Top.h"
#include "../../../headers/uvmenv_pseudo/components/Test.h"
#include "../../../headers/uvmenv_pseudo/components/Environment.h"

#include "../../../headers/uvmenv_pseudo/objects/Sequence.h"
#include "../../../headers/uvmenv_pseudo/objects/SequenceItem.h"
#include "../../../headers/uvmenv_pseudo/objects/RefModelImpl.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/component_handling/ptree_handling.h"
using namespace std;
using json = nlohmann::json;

vector<string> options = {"test", "env", "agent", "seqitem", "seqce", "scorebd", "refmod", "bfm"};
string ptree_file = PROJECT_DIR + PATH_SEP + "ptree.yml";


void createBFM(const string& name){
    string formatedName = "Bfm" + toPascalCase(name);
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

    unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
    vector<string> req_values;
    vector<string> res_values;

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), formatedName);


    json config = readFileJson(joinStr({
        PROJECT_DIR, "config.json"
    }, PATH_SEP));
    string topModule = config["dut_design"]["top_module"];
    
    for(const auto& [module, signalProps] : dutSignals) {
        // Create file content only with top module signals
        if(module == topModule){
            for (const auto& signal : signalProps) {
                if(signal.type == "INPUT"){
                    req_values.push_back(
                        doTabs(2)+"self.dut." + signal.name + ".value = self.__transaction." + signal.name
                    );
                }
                else if(signal.type == "OUTPUT"){
                    res_values.push_back(
                        doTabs(2)+"self.__transaction." + signal.name + " = self.dut." + signal.name + ".value"
                    );
                }
            }
        }
    }
    // Modify 'set' method
    content = regex_replace(content, regex("ASSIGN_REQ_VALUES"), joinStr(req_values, "\n") );

    // Modify 'get' method
    content = regex_replace(content, regex("ASSIGN_RES_VALUES"), joinStr(res_values, "\n") );

    // Write project file
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
    filesystem::copy(
        SIGREADER_FILEBASE,
        TBENCH_DIR + PATH_SEP + formatedName + PATH_SEP + "Misces" + PATH_SEP + "SignalsReader.py"
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
    string formatedName = "Sit" + toPascalCase(name);
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

void createAgent(const string& name, const string& testName, const string& envName, const string& type){
    // TODO: Use "type" to create specific kind of agents (active, passive or reactive)
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
    agent->setAgentType(type);
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




