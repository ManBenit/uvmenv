#include <iostream>
#include <filesystem>
#include "../../../headers/uvmenv_preudo/components/Top.h"
#include "../../../headers/functions/constants.h"
using namespace std;

Top* Top::m_instance = nullptr;

Top& Top::instance(){
    if(!m_instance){
        m_instance = new Top();
    }

    return *m_instance;
}

Top::Top(): UVMComponent("Top", "Top", nullptr){
    this -> basefilePath = BASES_REPRESENT_DIR + PATH_SEP + "TopBase.py";
    this -> uvmenvProjectDir = PROJECT_DIR;
}

void Top::setTopModuleName(const string& topModuleName){
    this -> topModuleName = topModuleName;
}

void Top::setProjectName(const string& projectName){
    this -> projectName = projectName;
}


// @Override
void Top::copyBaseFile(){
    filesystem::copy(
        basefilePath, 
        uvmenvProjectDir + PATH_SEP + projectName + PATH_SEP + "Top_" + topModuleName + ".py"
    );
    cout << "Copiar base del Top" << endl;
}



