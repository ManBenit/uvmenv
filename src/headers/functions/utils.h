#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include "constants.h"

using namespace std;
using json = nlohmann::json;

// ****************** INTERFACE UTIL FUNCTIONS ****************** //
void printError(string message);
void printInfo(string message);
void printWarning(string message);
void printOption(string option, string message);
int countCharOcurrences(char c, string str);
vector<string> splitString(const string& input, char delimiter);
void runCommandSimple(const string& sysCommand);
string runCommandReturn(const string& sysCommand);

// ****************** FRAMEWORK UTIL FUNCTIONS ****************** //
bool isUVMEnvProject();

// ********************* COMMANDS FUNCTIONS ********************* //
void showHelp();

// ****************** Python version ****************** //
string getPythonVersion();
void activatePythonVenv();
vector<string> getFileNamesInDirectory(const string directoryPath);
// ****************** Base 64 ****************** //
string base64_encode(const string &in);
string base64_decode(const string &in);

#endif // UTILS_H
