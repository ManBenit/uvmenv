#include "../../../headers/uvmenv_preudo/components/Driver.h"


// @Override
void Driver::printInfo() {
    cout << "[Driver] " << name << ", Parent: " << parent << endl;
}

void Driver::copyBasefile() {
    cout << "print base file of Driver" << endl;
}