#include "../../../headers/uvmenv_preudo/components/Top.h"
#include <iostream>
using namespace std;

Top* Top::m_instance = nullptr;

Top& Top::instance(){
    if(!m_instance){
        m_instance = new Top();
    }

    return *m_instance;
}

Top::Top(): UVMComponent("Top", nullptr){
    this -> basefilePath = "base top";
    this -> uvmenvProjectDir = "uvmenv dir";
}



// @Override
void Top::printInfo() {
    cout << "UVMEnv project Top" << endl;
}



