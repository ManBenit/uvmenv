#ifndef DELETE_COMPONENT_H
#define DELETE_COMPONENT_H

#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include "../../functions/utils.h"


// Require only name
void deleteBFMInterface     (const std::string& name);
void deleteTest             (const std::string& name);

// Require Test
void deleteSequence         (const std::string& name, const std::string& testName);
void deleteSeqitem          (const std::string& name, const std::string& testName);

void deleteEnvOnTest       (const std::string& name, const std::string& testName);

// Require Test and Environment
void deleteEnvOnEnv        (const std::string& name, const std::string& testName, const std::string& envParentName);

void deleteRefModel         (const std::string& name, const std::string& testName, const std::string& envName);
void deleteAgent            (const std::string& name, const std::string& testName, const std::string& envName);
void deleteScoreboard       (const std::string& name, const std::string& testName, const std::string& envName);


// UVMEnv characteristics
void deleteMiscelaneous     (const std::string& name, const std::string& testName);



#endif // DELETE_H

