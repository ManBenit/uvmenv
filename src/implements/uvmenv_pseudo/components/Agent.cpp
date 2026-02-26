#include <iostream>
#include "../../../headers/uvmenv_preudo/components/Agent.h"
using namespace std;


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
void Agent::copyBaseFile(){
    cout << "Copiar bases a la carpeta_alias" << endl;
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
}


// private
ComponentRegister<Agent> Agent::reg("Agent");


