#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../UVMComponent.h"
#include "../FactoryRegister.h"

class Scoreboard : public UVMComponent {

public:
    //Scoreboard(const std::string& name, UVMComponent* parent): UVMComponent(name, parent){}
    Scoreboard(const std::string& name, UVMComponent* parent): UVMComponent(name, parent){
        basefilePath = "sdfsdfdsf";
        uvmenvProjectDir = "43tf34f34f";
    }
    virtual ~Scoreboard() = default;
    void printInfo() override;

private:
    // auto registration
    static ComponentRegister<Scoreboard> reg;

};

#endif // SCOREBOARD_H

