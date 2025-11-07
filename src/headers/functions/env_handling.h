#ifndef ENV_HANDLING_H
#define ENV_HANDLING_H

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream> //*
#include "constants.h"
#include "utils.h"
using namespace std;

void createNewEnv(string projectName, string topModule);
void searchProjects();
void showModules();

#endif // ENV_HANDLING_H
