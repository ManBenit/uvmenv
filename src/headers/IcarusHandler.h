#ifndef ICARUS_HANDLER_H
#define ICARUS_HANDLER_H

#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "utils.h"
#include "constants.h"
using namespace std;

class IcarusHandler {
public:
    void compile();
    void getSignals();
};

#endif // ICARUS_HANDLER_H