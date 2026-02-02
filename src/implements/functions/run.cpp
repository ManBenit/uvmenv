#include "../../headers/functions/run.h"

void run(){
    printInfo("Starting UVMEnv verification run...");

    // Write Makefile
    writeMakefile();

    // Run make
    string make_cmd = "make -C " + getOutsimDir();
    execCmdSimple(make_cmd);

    // Execute simulation
    string sim_cmd = getOutsimDir() + "/simv";
    execCmdSimple(sim_cmd);

    printInfo("UVMEnv verification run completed.");
}

void writeMakefile(){
    string makefile_content =
        "TEST content\n";

    writeFile(getProjectDir() + "/Makefile", makefile_content);
}

