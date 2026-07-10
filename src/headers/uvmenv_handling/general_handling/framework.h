#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <string>
#include <initializer_list>
#include <unordered_map>
#include <vector>

class Signal;

bool isUVMEnvProject(const std::string& path);
bool existsDUT();
void showProjectTree();
void showReport();
void showWaveform();
void showCoverage();
void showHelp();
void createNewEnv(const std::string& projectName, const std::string& topModule);
void runCurrentProject(const std::string& waveLevel);
void searchProjects();
std::unordered_map<std::string, std::vector<Signal>> getDUTSignals(const char& option);
void printDUTSignals(const std::unordered_map<std::string, std::vector<Signal>>& dutSignals);


bool requireProject();
bool requireDUT();
bool requireArgs(std::initializer_list<std::string> args, const std::string& msg);
std::vector<Signal> runSignalsGetter(const std::string& module, char writeOption, char option);
void runVcdWriter(const std::string& topFile, const std::string& vcdLevel, const std::string& runningMode);

#endif // FRAMEWORK_H


