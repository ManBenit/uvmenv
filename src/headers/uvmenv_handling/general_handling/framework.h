#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <string>

bool isUVMEnvProject(const std::string& path);
void showHelp();
void createNewEnv(const std::string& projectName, const std::string& topModule);
void searchProjects();

#endif // FRAMEWORK_H


