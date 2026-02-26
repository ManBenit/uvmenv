#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <string>

bool isUVMEnvProject(const std::string& path);
void showHelp();
void createNewEnv(std::string projectName, std::string topModule);
void searchProjects();

#endif // FRAMEWORK_H


