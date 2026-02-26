#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Scoreboard.h"
using namespace std;


//


// @Override
void Scoreboard::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Scoreboard> Scoreboard::reg("Scoreboard");


