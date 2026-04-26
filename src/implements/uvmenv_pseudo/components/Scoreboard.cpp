#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Scoreboard.h"
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
    filesystem::copy(
        basefilePath, 
        TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Envmnt" + PATH_SEP + envName + PATH_SEP + "Scorbd" + PATH_SEP + name+".py"
    );
}


// private
ComponentRegister<Scoreboard> Scoreboard::reg("Scoreboard");


