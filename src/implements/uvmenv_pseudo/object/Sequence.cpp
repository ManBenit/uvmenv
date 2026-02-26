#include <iostream>
#include "../../../headers/uvmenv_preudo/objects/Sequence.h"
using namespace std;


//


// @Override
void Sequence::copyBaseFile(){
    cout << "Copiar archivo base de [object] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ObjectRegister<Sequence> Sequence::reg("Sequence");


