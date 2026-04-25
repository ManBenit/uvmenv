#ifndef CREATE_COMPONENT
#define CREATE_COMPONENT


#include <string>
#include <filesystem>
#include <vector>

class Test;
class Environment;



void createUVMEnvComponent(const std::string& type);
void listUVMEnvComponents(const std::string& type);
void editUVMEnvComponents(const std::string& type);
void deleteUVMEnvComponent(const std::string& type);



// name: with PascalCase
void createTest(const std::string& name);
void createSequence(const std::string& name, const std::string& testName);
void createSeqitem(const std::string& name, const std::string& testName);

void createEnvironment(const std::string& name, Test* test);
void createEnvironment(const std::string& name, Environment* env);

// name: with snake_case
void createAgent(const std::string& name, const std::string& attr, const std::string& module, Environment* env);

#endif

