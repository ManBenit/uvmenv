#ifndef PRE_PROJECT_H
#define PRE_PROJECT_H

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream> //*
#include "../../functions/constants.h"
#include "../../functions/utils.h"
#include "../../uvmenv_handling/general_handling/framework.h"
using namespace std;

void createNewEnv(string projectName, string topModule);
void searchProjects();

#endif // PRE_PROJECT_H