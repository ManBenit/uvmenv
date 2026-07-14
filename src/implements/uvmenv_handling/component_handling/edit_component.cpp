#include "../../../headers/uvmenv_handling/component_handling/edit_component.h"

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>
#include <vector>
#include <vector>

#include "../../../headers/uvmenv_pseudo/components/Top.h"
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

void editTest(const string& name){
    Test* test = (Test*) Factory::instance().createComponent("Test", name, &Top::instance());
    test->editFile(name);
}

void editSequence(const string& name, const string& testName){
    Sequence* sequence = (Sequence*) Factory::instance().createObject("Sequence", name);
    sequence->setTestContainer(testName);
    sequence->editFile(name);
}

void editSeqitem(const string& name, const string& testName){
    SequenceItem* seqitem = (SequenceItem*) Factory::instance().createObject("SequenceItem", name);
    seqitem->setTestContainer(testName);
    seqitem->editFile(name);
}

void editEnvironmentOnTest(const string& name, const string& testName){
    Environment* env    = (Environment*) Factory::instance().createComponent("Environment", name, nullptr);
    env->setTestContainer(testName);
    env->editFile(name);
}

void editEnvironmentOnEnv(const string& name, const string& testName, const string& envParentName){
    print("Comming soon...");
}

void editRefModel(const string& name, const string& testName, const string& envName){
    RefModelImpl* refmodel = (RefModelImpl*) Factory::instance().createObject("RefModelImpl", name);
    refmodel->setTestContainer(testName);
    refmodel->setEnvContainer(envName);
    refmodel->editFile(name);
}

void editAgent(const string& name, const string& testName, const string& envName, const string& agntComponent){
    Agent* agent = (Agent*) Factory::instance().createComponent("Agent", name, nullptr);
    agent->setTestContainer(testName);
    agent->setEnvContainer(envName);
    agent->editFile(name, agntComponent);
}

void editScoreboard(const string& name, const string& testName, const string& envName){
    Scoreboard* scoreboard = (Scoreboard*) Factory::instance().createComponent("Scoreboard", name, nullptr);
    scoreboard->setTestContainer(testName);
    scoreboard->setEnvContainer(envName);
    scoreboard->copyBaseFile();
}




