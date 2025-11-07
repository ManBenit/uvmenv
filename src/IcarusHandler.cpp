#include "headers/IcarusHandler.h"

void IcarusHandler::compile(vector<string> files, string topModule) {
    string outputFile = getOutsimDir() + "/simv";
    string compileCommand = "iverilog -o " + string(OUTSIM_DIR) + ;
    
    // Add all Verilog files in the src directory
    for (const auto& entry : filesystem::recursive_directory_iterator(SRC_DIR)) {
        if (entry.path().extension() == ".v" || entry.path().extension() == ".sv") {
            compileCommand += entry.path().string() + " ";
        }
    }

    compileCommand += "-I " + string(SRC_DIR) + " -D UVM_NO_DEPRECATED";

    int ret = system(compileCommand.c_str());
    if (ret != 0) {
        printError("Compilation failed.");
        exit(1);
    }
    printInfo("Compilation successful.");
}

void IcarusHandler::getSignals() {
    printInfo("Extracting signals with Icarus Verilog...");

    // Run the simulation to generate VCD file
    string simCommand = string(OUTSIM_DIR) + "/simv +vcdfile=" + string(OUTSIM_DIR) + "/dut_signals.vcd";
    int ret = system(simCommand.c_str());
    if (ret != 0) {
        printError("Simulation failed.");
        exit(1);
    }

    printInfo("Signal extraction complete. VCD file generated at " + string(OUTSIM_DIR) + "/dut_signals.vcd");
}