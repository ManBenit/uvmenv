#include "../../../headers/uvmenv_pseudo/objects/SequenceItem.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <cmath>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


void SequenceItem::setName(const string& name){
    this->name = name;
}

void SequenceItem::setTestContainer(const string& testName){
    this->testName = testName;
}


// @Override
void SequenceItem::copyBaseFile(){
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

    // // Modify class name
    // content = regex_replace(content, regex("CLASS_NAME"), name);

    json config = readFileJson(joinStr({
        PROJECT_DIR, "config.json"
    }, PATH_SEP));
    string topModule = config["dut_design"]["top_module"];

    long randMax = 0;
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
                        doTabs(3)+"'" + signal.name + "': hex(self." + signal.name + ")"
                    );
                }
                else if(signal.type == "OUTPUT"){
                    the_outputs.push_back(
                        doTabs(3)+"'" + signal.name + "': hex(self." + signal.name + ")"
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
    
    ofstream outFile(joinStr({
        TBENCH_DIR, testName, "SeqItm", name+".py"
    }, PATH_SEP));
    outFile << content;
}


// private
ObjectRegister<SequenceItem> SequenceItem::reg("SequenceItem");


