#include <iostream>
#include "../../../headers/uvmenv_preudo/objects/RefModelImpl.h"
using namespace std;


void RefModelImpl::setName(const string& name){
    this->name = name;
}

void RefModelImpl::setTestContainer(const string& testName){
    this->testName = testName;
}

void RefModelImpl::setEnvContainer(const string& envName){
    this->envName = envName;
}


// @Override
void RefModelImpl::copyBaseFile(){
    filesystem::copy(
        basefilePath, 
        TBENCH_DIR + PATH_SEP + testName + PATH_SEP + "Envmnt" + PATH_SEP + envName + PATH_SEP + "RefMdl" + PATH_SEP + "_impl" + PATH_SEP + name+".py"
    );
}


// private
ObjectRegister<RefModelImpl> RefModelImpl::reg("RefModelImpl");


