
#include "../../../headers/uvmenv_pseudo/components/Scoreboard.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <fstream>
using namespace std;


void Scoreboard::setName(const string& name){
    this->name = name;
}

void Scoreboard::setTestContainer(const string& testName){
    this->testName = testName;
}

void Scoreboard::setEnvContainer(const string& envName){
    this->envName = envName;
}


// @Override
void Scoreboard::copyBaseFile(){
    ifstream baseFile(basefilePath);
    stringstream buffer;
    buffer << baseFile.rdbuf();
    string content = buffer.str();

    // Modify class name
    content = regex_replace(content, regex("CLASS_NAME"), name);

    // Write project file
    ofstream testFile(joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "Scorbd", name+".py"
    }, PATH_SEP));
    testFile << content;
}


// private
ComponentRegister<Scoreboard> Scoreboard::reg("Scoreboard");


