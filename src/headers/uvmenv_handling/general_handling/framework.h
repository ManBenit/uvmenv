#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <string>
#include <initializer_list>

bool isUVMEnvProject(const std::string& path);
bool existsDUT();
void showProjectTree();
void showReport();
void showWaveform();
void showHelp();
void createNewEnv(const std::string& projectName, const std::string& topModule);
void runCurrentProject();
void searchProjects();
void getDUTSignals(const char& option);


bool requireProject();
bool requireDUT();
bool requireArgs(std::initializer_list<std::string> args, const std::string& msg);


#endif // FRAMEWORK_H


