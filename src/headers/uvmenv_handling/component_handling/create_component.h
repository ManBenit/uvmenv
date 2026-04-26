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



void createTest(const std::string& name);
void createSequence(const std::string& name, const std::string& testName);
void createSeqitem(const std::string& name, const std::string& testName);

void createEnvironmentOnTest(const std::string& name, const std::string& testName);
void createEnvironmentOnEnv(const std::string& name, const std::string& envParentName, const std::string& testName);

void createRefModel(const std::string& name, const std::string& envName, const std::string& testName);
void createAgent(const std::string& name, const std::string& envName, const std::string& testName);
void createScoreboard(const std::string& name, const std::string& envName, const std::string& testName);

void createBFM(const std::string& name);

#endif

