#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/uvmenv_handling/project_handling/run.h"
using namespace std;

void run(){
    printInfo("Starting UVMEnv verification run...");

    // Write Makefile
    writeMakefile();

    // Run make
    string make_cmd = "make -C " + OUTSIM_DIR;
    //execCmdSimple(make_cmd);

    // Execute simulation
    string sim_cmd = OUTSIM_DIR + "/simv";
    //execCmdSimple(sim_cmd);

    printInfo("UVMEnv verification run completed.");
}

void writeMakefile(){
    string makefile_content =
        "TEST content\n";

    writeFile(PROJECT_DIR + "/Makefile", makefile_content);
}

