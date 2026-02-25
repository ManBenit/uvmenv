#include "../../../headers/uvmenv_preudo/components/Scoreboard.h"

Scoreboard::Scoreboard(const string& name, const string& parent){
    basefilePath = "sdfsdfdsf";
    uvmenvProjectDir = "43tf34f34f";
}


// @Override
void Scoreboard::printInfo() {
    cout << "[Scoreboard] " << name << ", Parent: " << parent << endl;
    cout << "basefile: " << basefilePath << endl;
    cout << "dir: " << uvmenvProjectDir << endl;
}

void Scoreboard::copyBasefile() {
    cout << "print base file of Scoreboard" << endl;
}


// private
ComponentRegister<Scoreboard> Scoreboard::reg("Scoreboard");


