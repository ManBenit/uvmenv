#ifndef EDIT_COMPONENT_H
#define EDIT_COMPONENT_H


#include <string>
#include <filesystem>
#include <vector>


// Require only name
void editBFM                (const std::string& name);
void editTest               (const std::string& name);

// Require Test
void editSequence           (const std::string& name, const std::string& testName);
void editSeqitem            (const std::string& name, const std::string& testName);

void editEnvironmentOnTest  (const std::string& name, const std::string& testName);

// Require Test and Environment
void editEnvironmentOnEnv   (const std::string& name, const std::string& testName, const std::string& envParentName);

void editRefModel           (const std::string& name, const std::string& testName, const std::string& envName);
void editAgent              (const std::string& name, const std::string& testName, const std::string& envName);
void editScoreboard         (const std::string& name, const std::string& testName, const std::string& envName);

#endif // EDIT_COMPONENT_H

