#include <iostream>
#include "../../../headers/uvmenv_preudo/objects/RefModelImpl.h"
using namespace std;


//


// @Override
void RefModelImpl::copyBaseFile(){
    cout << "Copiar archivo base de [object] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ObjectRegister<RefModelImpl> RefModelImpl::reg("RefModelImpl");


