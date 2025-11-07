#ifndef VERILATOR_HANDLER_H
#define VERILATOR_HANDLER_H

#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <vector>
#include "utils.h"
#include "constants.h"
using namespace std;

class VerilatorHandler {
public:
    void compileForAPI(vector<string> srcFiles, string topModule);
    void compileWithoutExe(vector<string> srcFiles, string topModule);

    string getSignals();
};

#endif // VERILATOR_HANDLER_H