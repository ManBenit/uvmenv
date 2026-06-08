#include "../../../headers/uvmenv_pseudo/objects/SequenceItem.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <cmath>
using namespace std;


void SequenceItem::setName(const string& name){
    this->name = name;
}

void SequenceItem::setTestContainer(const string& testName){
    this->testName = testName;
}


// @Override
void SequenceItem::copyBaseFile(){
    string newSeqitemPath = joinStr({
        TBENCH_DIR, testName, "SeqItm", name
    }, PATH_SEP);  
    
    filesystem::create_directory(newSeqitemPath);
    filesystem::copy(
        requestBasePath, 
        newSeqitemPath + PATH_SEP + "Request.py"
    );
    filesystem::copy(
        responseBasePath, 
        newSeqitemPath + PATH_SEP + "Response.py"
    );


    ifstream baseRequest(requestBasePath);
    stringstream bufferRequest;
    bufferRequest << baseRequest.rdbuf();
    string contentRequest = bufferRequest.str();

    ifstream baseResponse(responseBasePath);
    stringstream bufferResponse;
    bufferResponse << baseResponse.rdbuf();
    string contentResponse = bufferResponse.str();

    unordered_map<string, vector<Signal>> dutSignals = getDUTSignals('n');
    vector<string> res_input_lines;
    vector<string> res_output_lines;
    vector<string> res_input_lines_str;
    vector<string> res_output_lines_str;
    vector<string> res_input_lines_str_nointeger;
    vector<string> res_output_lines_str_nointeger;
    vector<string> req_input_lines;
    vector<string> req_rand_input_lines;
    vector<string> req_input_lines_str;

    // // Modify class name
    // content = regex_replace(content, regex("CLASS_NAME"), name);
    long randMax = 0;
    for(const auto& [signalName, signalProps] : dutSignals) {
        for (const auto& signal : signalProps) {
            if(signal.type == "INPUT"){
                randMax = pow(2, signal.size) - 1;
                res_input_lines.push_back(
                    doTabs(4)+"'" + signal.name + "': self.ins['" + signal.name + "']"
                );
                res_input_lines_str.push_back(
                    doTabs(5)+"'" + signal.name + "': hex(self.ins['" + signal.name + "'].integer)"
                );
                res_input_lines_str_nointeger.push_back(
                    doTabs(5)+"'" + signal.name + "': self.ins['" + signal.name + "']"
                );
                req_input_lines.push_back(
                    doTabs(2)+"self." + signal.name + " = 0"
                );
                req_rand_input_lines.push_back(
                    doTabs(2)+"self." + signal.name + " = random.randint(0, " + to_string(randMax) + ")"
                );
                req_input_lines_str.push_back(
                    doTabs(3)+"'" + signal.name + "': self." + signal.name
                );
            }
            else if(signal.type == "OUTPUT"){
                res_output_lines.push_back(
                    doTabs(4)+"'" + signal.name + "': self.outs['" + signal.name + "']"
                );
                res_output_lines_str.push_back(
                    doTabs(5)+"'" + signal.name + "': hex(self.outs['" + signal.name + "'].integer)"
                );
                res_output_lines_str_nointeger.push_back(
                    doTabs(5)+"'" + signal.name + "': self.outs['" + signal.name + "']"
                );
            }
        }
    }
    // Modify request
    contentRequest = regex_replace(contentRequest, 
        regex("ATTRIB_SIGNALS"), joinStr(req_input_lines, "\n")
    );
    contentRequest = regex_replace(contentRequest, 
        regex("RANDOM_SIGNALS"), joinStr(req_rand_input_lines, "\n")
    );
    contentRequest = regex_replace(contentRequest, 
        regex("ATTRIB_STR_SIGNALS"), joinStr(req_input_lines_str, ",\n")
    );

    // Modify response
    contentResponse = regex_replace(contentResponse, 
        regex("THE_INPUTS"), joinStr(res_input_lines, ",\n") 
    );
    contentResponse = regex_replace(contentResponse, 
        regex("THE_OUTPUTS"), joinStr(res_output_lines, ",\n") 
    );
    contentResponse = regex_replace(contentResponse, 
        regex("THE_STR_NOINT_INPUTS"), joinStr(res_input_lines_str_nointeger, ",\n") 
    );
    contentResponse = regex_replace(contentResponse, 
        regex("THE_STR_INPUTS"), joinStr(res_input_lines_str, ",\n") 
    );
    contentResponse = regex_replace(contentResponse, 
        regex("THE_STR_NOINT_OUTPUTS"), joinStr(res_output_lines_str_nointeger, ",\n") 
    );
    contentResponse = regex_replace(contentResponse, 
        regex("THE_STR_OUTPUTS"), joinStr(res_output_lines_str, ",\n") 
    );
    
    // Write project file
    ofstream requestFile(joinStr({
        newSeqitemPath, "Request.py"
    }, PATH_SEP));
    requestFile << contentRequest;

    ofstream responseFile(joinStr({
        newSeqitemPath, "Response.py"
    }, PATH_SEP));
    responseFile << contentResponse;


    filesystem::copy(
        basefilePath,
        joinStr({newSeqitemPath, "__init__.py"}, PATH_SEP)
    );
}


// private
ObjectRegister<SequenceItem> SequenceItem::reg("SequenceItem");


