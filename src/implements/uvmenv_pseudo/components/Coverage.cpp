#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Coverage.h"
using namespace std;


//


// @Override
void Coverage::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Coverage> Coverage::reg("Coverage");


