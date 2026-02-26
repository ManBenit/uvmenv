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

#include "../../headers/functions/constants.h"
#include "../../headers/functions/utils.h"
using namespace std;
using json = nlohmann::json;



// ****************** INTERFACE UTIL FUNCTIONS ****************** //
void printError(string message){
    cout << C_RED << message << C_N << endl;
}

void printInfo(string message){
    cout << C_GREEN << message << C_N << endl;
}

void printWarning(string message){
    cout << C_YELLOW << message << C_N << endl;
}

void printOption(string option, string message){
    cout << "     " << C_CYAN << option << C_N << "\n\t" << message << endl;
}

int countCharOcurrences(char c, string str) {
    int count = 0;

    for (char i : str)
        if (i == c) count++;

    return count;
}

vector<string> splitString(const string& input, char delimiter) {
    vector<string> tokens;
    istringstream stream(input);
    string token;

    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string trim(const string& s){
    // Look for the first character different to whithe space
    size_t first = s.find_first_not_of(WHITESPACE);
    
    // Not found => is all empty, so return empty
    if (first == std::string::npos) 
        return "";
    
    // Look for the last character different to whithe space
    size_t last = s.find_last_not_of(WHITESPACE);
    
    return s.substr(first, (last - first + 1));
}
////////////////////////////////////////////////////////////////////



// ****************** Base 64 ****************** //
string base64_encode(const string &in) {
    static const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string out;
    int val = 0, valb = -6;

    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    return out;
}


string base64_decode(const string &in) {
    static const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[chars[i]] = i;

    string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}
///////////////////////////////////////////////////////////////////


// ***************** File writing/reading/research ***************** //
void writeFile(const string filePath, const string content) {
    ofstream outFile(filePath);
    if (!outFile) {
        printError("Error opening file for writing: " + filePath);
        return;
    }
    outFile << content;
    outFile.close();
}

string readFile(const string filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        printError("Error opening file for reading: " + filePath);
        return "";
    }
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return content;
}

vector<string> getFileNamesInDirectory(const string directoryPath) {
    vector<string> fileNames;

    try {
        for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                fileNames.push_back(entry.path().filename().string());
            } else if (entry.is_directory()) {
                // Get internal files recursively
                vector<string> subFiles = getFileNamesInDirectory(entry.path().string());
                for (const auto& subFile : subFiles) {
                    fileNames.push_back(entry.path().filename().string() + "/" + subFile);
                }
            }
        }
    } catch (const filesystem::filesystem_error& e) {
        cerr << "Error accediendo al directorio: " << e.what() << endl;
    }

    return fileNames;
}
///////////////////////////////////////////////////////////////////

