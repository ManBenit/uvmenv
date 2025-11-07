#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

class Agent {
private:
    int monitor;
    int driver;
    int coverageCollector;
    //int sequencer; // Implicit on Python implementation
    int type;

public:
    void create();
    void show();
    void erase();
    void edit();
    string to_string();
};


#endif // AGENT_H

