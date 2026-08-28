#include "../../../include/uvmenv_pseudo/objects/SequenceItem.h"

#include "../../../include/functions/utils.h"
#include "../../../include/uvmenv_handling/general_handling/pconfig_handling.h"
#include "../../../include/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../include/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <cmath>
#include <filesystem>
using namespace std;


void SequenceItem::setName(const string& name){
    this->name = name;
}

void SequenceItem::setTestContainer(const string& testName){
    this->testName = testName;
}

void SequenceItem::editFile(const string& name){
    uvmenvProjectDir = joinStr({
        TBENCH_DIR, testName, "SeqItm", name+".py"
    }, PATH_SEP);
    const string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDir;
    
    if(!filesystem::exists(uvmenvProjectDir)){
        printError("[Sequence item] Does not exist " + name);
        exit(5);
    }
    
    int sysResult = system(file.c_str());
    if (sysResult== 0) {
        printInfo("Finished edition of " + name);
    } else {
        printError( "Something went wrong while editing " + name + ". Returned code " + to_string(sysResult) );
    }
}

void SequenceItem::deleteFile(const string& name){
    const string toDelete = joinStr({
        TBENCH_DIR, testName, "SeqItm", name+".py"
    }, PATH_SEP);
    
    if(!filesystem::exists(toDelete)){
        printError("[Sequence item] Does not exist " + name);
        exit(5);
    }
    
    filesystem::remove(toDelete);
}


// @Override
void SequenceItem::copyBaseFile(){
    uvmenvProjectDir = joinStr({
        TBENCH_DIR, testName, "SeqItm", name+".py"
    }, PATH_SEP);


    string seqitemPath = joinStr({
        TBENCH_DIR, testName, "SeqItm", name
    }, PATH_SEP);  

    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();


    unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
    vector<string> attrib_signals;
    vector<string> random_signals;
    vector<string> the_inputs;
    vector<string> the_outputs;
    vector<string> the_unkn_values;

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    string topModule = getProjectDutDesign(PROJECT_DIR, "top_module");

    long long randMax = 0;
    for(const auto& [module, signalProps] : dutSignals) {
        if(module == topModule){
            for (const auto& signal : signalProps) {
                randMax = pow(2, signal.size) - 1;

                attrib_signals.push_back(
                    doTabs(2)+"self." + signal.name + " = 0"
                );

                if(signal.type == "INPUT"){
                    random_signals.push_back(
                        doTabs(2)+"self." + signal.name + " = random.randint(0, " + to_string(randMax) + ")"
                    );
                    the_inputs.push_back(
                        doTabs(3)+"'" + signal.name + "': self." + signal.name
                    );
                }
                else if(signal.type == "OUTPUT"){
                    the_outputs.push_back(
                        doTabs(4)+"'" + signal.name + "': self." + signal.name
                    );
                    the_unkn_values.push_back(
                        doTabs(4)+"'" + signal.name + "': process_unkn_val(self." + signal.name + ")"
                    );
                }
            }
        }
    }
    
    content = regex_replace(content, 
        regex("ATTRIB_SIGNALS"), joinStr(attrib_signals, "\n")
    );
    content = regex_replace(content, 
        regex("RANDOM_SIGNALS"), joinStr(random_signals, "\n")
    );
    content = regex_replace(content, 
        regex("THE_INPUTS"), joinStr(the_inputs, ",\n")
    );
    content = regex_replace(content, 
        regex("THE_OUTPUTS"), joinStr(the_outputs, ",\n") 
    );
    content = regex_replace(content, 
        regex("THE_UNKN_OUTPUTS"), joinStr(the_unkn_values, ",\n") 
    );
    
    ofstream outFile(uvmenvProjectDir);
    outFile << content;
    outFile.close();
}


// private
ObjectRegister<SequenceItem> SequenceItem::reg("SequenceItem");


