#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <string>
#include <iostream>
#include <vector>
#include <array>

#include "../../functions/utils.h"

using namespace std;


void execCmdSimple(const string& cmd); // toHandling
string execCmdReturn(const string& cmd); // toHandling

bool isUVMEnvProject(); // toHandling
string getScript(const string& name); // toHandling

string getPythonVersion(); // toHandling
void activatePythonVenv(); // toHandling

void showHelp(); // toHandling

#endif // FRAMEWORK_H
