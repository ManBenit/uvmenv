#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <string>
#include <initializer_list>
#include <unordered_map>
#include <vector>

struct Signal {
    std::string name;
    std::string type;
    int size;
};

bool isUVMEnvProject(const std::string& path);
bool existsDUT();
void showProjectTree();
void showReport();
void showWaveform();
void showHelp();
void createNewEnv(const std::string& projectName, const std::string& topModule);
void runCurrentProject();
void searchProjects();
std::unordered_map<std::string, std::vector<Signal>> getDUTSignals(const char& option);
void printDUTSignals(const std::unordered_map<std::string, std::vector<Signal>>& dutSignals);


bool requireProject();
bool requireDUT();
bool requireArgs(std::initializer_list<std::string> args, const std::string& msg);
std::vector<Signal> runSignalsGetter(const std::string& module, char writeOption, char option);

#endif // FRAMEWORK_H


