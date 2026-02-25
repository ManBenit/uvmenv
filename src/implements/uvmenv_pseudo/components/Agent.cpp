#include "../../../headers/uvmenv_preudo/components/Agent.h"


void Agent::setDriver(Driver* d) { 
    driver = d; 
}

void Agent::setMonitor(Monitor* m) { 
    monitor = m; 
}

void Agent::setCoverage(Coverage* c) { 
    coverage = c; 
}

Driver* Agent::getDriver() { 
    return driver; 
}
Monitor* Agent::getMonitor() { 
    return monitor; 
}

Coverage* Agent::getCoverage() { 
    return coverage; 
}



// @Override
void Agent::printInfo() {
    cout << "[Agent] " << name << ", Parent: " << parent << endl;
}

void Agent::copyBasefile() {
    cout << "print base file of Agent" << endl;
}
