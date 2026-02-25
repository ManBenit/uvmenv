#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Scoreboard.h"
using namespace std;


// @Override
void Scoreboard::printInfo() {
    cout << "[Scoreboard] " << name << ", Parent: " << parent->getName() << endl;
}


// private
ComponentRegister<Scoreboard> Scoreboard::reg("Scoreboard");


