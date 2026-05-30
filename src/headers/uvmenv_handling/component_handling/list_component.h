#ifndef LIST_COMPONENT_H
#define LIST_COMPONENT_H

#include <string>
#include <filesystem>
#include <vector>


// Require only name
std::vector<std::string> listBFMInterfaces ();
std::vector<std::string> listTests();

// Require Test
std::vector<std::string> listSequences         (const std::string& testName);
std::vector<std::string> listSeqitems          (const std::string& testName);

std::vector<std::string> listEnvsOnTest(const std::string& testName);

// Require Test and Environment
std::vector<std::string> listEnvsOnEnv (const std::string& testName, const std::string& envParentName);

std::vector<std::string> listRefModels  (const std::string& testName, const std::string& envName);
std::vector<std::string> listAgents     (const std::string& testName, const std::string& envName);
std::vector<std::string> listScoreboards(const std::string& testName, const std::string& envName);


#endif // LIST_H

