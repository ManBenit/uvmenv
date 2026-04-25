#include <iostream>
#include "../../../headers/uvmenv_preudo/objects/Sequence.h"
using namespace std;


void Sequence::setName(const string& name){
    this->name = name;
}

void Sequence::setTestContainer(const string& testName){
    this->testName = testName;
}

// @Override
void Sequence::copyBaseFile(){
    filesystem::copy(
        basefilePath, 
        TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Seqnce" + PATH_SEP + name+".py"
    );
}


// private
ObjectRegister<Sequence> Sequence::reg("Sequence");


