#include <iostream>
#include "../../../headers/uvmenv_preudo/objects/SequenceItem.h"
using namespace std;


void SequenceItem::setName(const string& name){
    this->name = name;
}

void SequenceItem::setTestContainer(const string& testName){
    this->testName = testName;
}


// @Override
void SequenceItem::copyBaseFile(){
    string newSeqitemPath = TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "SeqItm" + PATH_SEP + name;
    filesystem::create_directory(newSeqitemPath);
    filesystem::copy(
        requestBasePath, 
        newSeqitemPath + PATH_SEP + "Request.py"
    );
    filesystem::copy(
        responseBasePath, 
        newSeqitemPath + PATH_SEP + "Response.py"
    );
}


// private
ObjectRegister<SequenceItem> SequenceItem::reg("SequenceItem");


