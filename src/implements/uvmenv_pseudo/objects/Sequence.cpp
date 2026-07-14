#include "../../../headers/uvmenv_pseudo/objects/Sequence.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <filesystem>
#include <fstream>
using namespace std;


void Sequence::setName(const string& name){
    this->name = name;
}

void Sequence::setTestContainer(const string& testName){
    this->testName = testName;
}

void Sequence::editFile(const string& name){
    uvmenvProjectDir = joinStr({TBENCH_DIR, testName, "Seqnce", name+".py"}, PATH_SEP);
    const string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDir;
    
    if(!filesystem::exists(uvmenvProjectDir)){
        printError("[Sequence] Does not exist " + name);
        exit(5);
    }
    
    int sysResult = system(file.c_str());
    if (sysResult== 0) {
        printInfo("Finished edition of " + name);
    } else {
        printError( "Something went wrong while editing " + name + ". Returned code " + to_string(sysResult) );
    }
}


// @Override
void Sequence::copyBaseFile(){
    uvmenvProjectDir = joinStr({TBENCH_DIR, testName, "Seqnce", name+".py"}, PATH_SEP);

    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    // Write project file
    ofstream outFile(uvmenvProjectDir);
    outFile << content;
    outFile.close();
}


// private
ObjectRegister<Sequence> Sequence::reg("Sequence");


