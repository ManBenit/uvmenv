#ifndef LIST_COMPONENT_H
#define LIST_COMPONENT_H

#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include "../../functions/utils.h"

class Signal;

// Require only name
std::vector<std::string> listBFMInterfaces ();
std::vector<std::string> listTests();

// Require Test
std::vector<std::string> listSequences         (const std::string& testName);
std::vector<std::string> listSeqitems          (const std::string& testName);

std::vector<std::string> listEnvsOnTest        (const std::string& testName);

// Require Test and Environment
std::vector<std::string> listEnvsOnEnv         (const std::string& testName, const std::string& envParentName);

std::vector<std::string> listRefModels         (const std::string& testName, const std::string& envName);
std::vector<std::string> listAgents            (const std::string& testName, const std::string& envName);
std::vector<std::string> listScoreboards       (const std::string& testName, const std::string& envName);


// UVMEnv characteristics
std::vector<std::string> listMiscelaneous      (const std::string& testName);
std::unordered_map<std::string, std::vector<Signal>> listRtlSignals();
std::vector<std::string> listRtlModules();



#endif // LIST_H

