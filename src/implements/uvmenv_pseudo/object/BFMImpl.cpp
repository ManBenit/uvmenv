#include <iostream>
#include "../../../headers/uvmenv_preudo/objects/BFMImpl.h"
using namespace std;


//


// @Override
void BFMImpl::copyBaseFile(){
    cout << "Copiar archivo base de [object] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ObjectRegister<BFMImpl> BFMImpl::reg("BFMImpl");


