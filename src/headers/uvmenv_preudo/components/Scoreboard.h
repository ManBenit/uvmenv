#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../UVMComponent.h"
#include "../FactoryRegister.h"
using namespace std;

class Scoreboard : public UVMComponent {

public:
    Scoreboard(const string& name, const string& parent);
    virtual ~Scoreboard() = default;
    void printInfo() override;
    void copyBasefile() override;

private:
    // auto registration
    static ComponentRegister<Scoreboard> reg;

};

#endif // SCOREBOARD_H

