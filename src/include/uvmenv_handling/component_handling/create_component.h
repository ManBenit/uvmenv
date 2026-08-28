#ifndef CREATE_COMPONENT_H
#define CREATE_COMPONENT_H


#include <string>
#include <filesystem>
#include <vector>


// Require only name
void createBFM                (const std::string& name);
void createTest               (const std::string& name);

// Require Test
void createSequence           (const std::string& name, const std::string& testName);
void createSeqitem            (const std::string& name, const std::string& testName);

void createEnvironmentOnTest  (const std::string& name, const std::string& testName);

// Require Test and Environment
void createEnvironmentOnEnv   (const std::string& name, const std::string& testName, const std::string& envParentName);

void createRefModel           (const std::string& name, const std::string& testName, const std::string& envName);
void createAgent              (const std::string& name, const std::string& testName, const std::string& envName, const std::string& type);
void createScoreboard         (const std::string& name, const std::string& testName, const std::string& envName);

#endif // CREATE_COMPONENT_H

