#include <iostream>
#include "../../../headers/uvmenv_pseudo/components/Monitor.h"
using namespace std;


//


// @Override
void Monitor::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Monitor> Monitor::reg("Monitor");


