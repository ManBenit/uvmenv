
#include "../../../headers/uvmenv_pseudo/components/Scoreboard.h"

#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"

#include <iostream>
#include <regex>
#include <filesystem>
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

void Scoreboard::editFile(const string& name){
    const string file = getScript("sys_commands")+"openEditor " + uvmenvProjectDirPrefix  + PATH_SEP + name+".py";
    
    if(!filesystem::exists(uvmenvProjectDir)){
        printError("Does not exist " + name);
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
void Scoreboard::copyBaseFile(){
    uvmenvProjectDir = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "Scorbd", name+".py"
    }, PATH_SEP);

    uvmenvProjectDirPrefix = joinStr({
        TBENCH_DIR, testName, "Envmnt", envName, "Scorbd"
    }, PATH_SEP);

    
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
ComponentRegister<Scoreboard> Scoreboard::reg("Scoreboard");


