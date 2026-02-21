#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Factory.h"
using namespace std;

class Scoreboard : public UVMComponent {
public:
    void printInfo() override {
        cout << "[Scoreboard] " << name << ", Parent: " << parent << endl;
    }
};

#endif // SCOREBOARD_H

