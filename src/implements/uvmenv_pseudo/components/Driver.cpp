#include <iostream>
#include "../../../headers/uvmenv_pseudo/components/Driver.h"
using namespace std;


//

// @Override
void Driver::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Driver> Driver::reg("Driver");



