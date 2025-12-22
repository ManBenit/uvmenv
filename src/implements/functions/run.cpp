#include "../../headers/functions/run.h"

void run(){
    printInfo("Starting UVMEnv verification run...");

    // Write Makefile
    writeMakefile();

    // Run make
    string make_cmd = "make -C " + getOutsimDir();
    runCommandSimple(make_cmd);

    // Execute simulation
    string sim_cmd = getOutsimDir() + "/simv";
    runCommandSimple(sim_cmd);

    printInfo("UVMEnv verification run completed.");
}

