#include "../../../headers/uvmenv_preudo/components/Top.h"
#include "../../../headers/functions/constants.h"
#include <iostream>
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
    this -> uvmenvProjectDir = PROJECT_DIR; //AddAliasForNewProject
}


// @Override
void Top::copyBaseFile(){
    cout << "Copiar base del Top" << endl;
}


