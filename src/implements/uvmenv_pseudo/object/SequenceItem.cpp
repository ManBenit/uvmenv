#include <iostream>
#include "../../../headers/uvmenv_preudo/objects/SequenceItem.h"
using namespace std;


//


// @Override
void SequenceItem::copyBaseFile(){
    cout << "Copiar archivo base de [object] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ObjectRegister<SequenceItem> SequenceItem::reg("SequenceItem");


