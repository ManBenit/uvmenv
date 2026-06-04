#include "../../../headers/uvmenv_pseudo/objects/Sequence.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
using namespace std;


void Sequence::setName(const string& name){
    this->name = name;
}

void Sequence::setTestContainer(const string& testName){
    this->testName = testName;
}

// @Override
void Sequence::copyBaseFile(){
    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    // Write project file
    ofstream testFile(joinStr({TBENCH_DIR, testName, "Seqnce", name+".py"}, PATH_SEP));
    testFile << content;
}


// private
ObjectRegister<Sequence> Sequence::reg("Sequence");


