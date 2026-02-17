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
#include <array>
#include <stdexcept>
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


// ****************** Base 64 ****************** //
string base64_encode(const string &in);
string base64_decode(const string &in);

// ****************** File operations ****************** //
void writeFile(const string filePath, const string content);
string readFile(const string filePath);
vector<string> getFileNamesInDirectory(const string directoryPath);

#endif // UTILS_H
