#include "../../../headers/uvmenv_preudo/components/Monitor.h"

// @Override
void Monitor::printInfo() {
    cout << "[Monitor] " << name << ", Parent: " << parent << endl;
}

void Monitor::copyBasefile() {
    cout << "print base file of Monitor" << endl;
}


