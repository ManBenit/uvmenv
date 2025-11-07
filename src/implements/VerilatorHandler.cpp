#include "../headers/VerilatorHandler.h"

// ****************** Verilator Handler ****************** //
void VerilatorHandler::compileForAPI(vector<string> srcFiles, string topModule) {
    string outDir = getOutsimDir() + "/verilator_build";
    string cmd = "";

    cmd += "verilator --cc -Mdir "+outDir+" -Wno-WIDTHEXPAND -Wno-fatal";
    cmd += " --trace --x-assign unique --x-initial unique --hierarchical";
    cmd += " --exe --build -CFLAGS \"-fPIC\" -LDFLAGS \"-shared\"";
    cmd += " LOSARCHIVOSXD";
    cmd += " --top-module " + topModule;
    cmd += "-o libalu.so";
}

void VerilatorHandler::compileWithoutExe(vector<string> srcFiles, string topModule) {
    string outDir = getOutsimDir() + "/verilator_build";
    string cmd = "";

    cmd += "verilator --cc -Mdir "+outDir+" -Wno-WIDTHEXPAND -Wno-fatal";
    cmd += " --trace --x-assign unique --x-initial unique --hierarchical";
    cmd += " LOSARCHIVOSXD";
    cmd += " --top-module " + topModule;
}


