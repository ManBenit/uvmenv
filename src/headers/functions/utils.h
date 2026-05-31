#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>


const std::string WHITESPACE = " \n\r\t\f\v";

// ****************** INTERFACE UTIL FUNCTIONS ****************** //
void print(std::string message);
void printError(std::string message);
void printInfo(std::string message);
void printWarning(std::string message);
void printOption(std::string option, std::string message);
int countCharOcurrences(char c, std::string str);
std::vector<std::string> splitString(const std::string& input, char delimiter);
std::string trim(const std::string& s);
bool isPascalCase(const std::string& s);
std::string toPascalCase(const std::string& texto);
bool isSnakeCase(const std::string& s);
std::string toSnakeCase(const std::string& texto);
bool isInOptions(const std::string& value, const std::vector<std::string>* options);


// ****************** Base 64 ****************** //
std::string base64_encode(const std::string &in);
std::string base64_decode(const std::string &in);

// ****************** File operations ****************** //
void writeFile(const std::string filePath, const std::string content);
std::string readFile(const std::string filePath);
void writeFileJson(const std::string& filePath, const nlohmann::ordered_json& jsonData);
nlohmann::ordered_json readFileJson(const std::string& filePath);
void writeFileYaml(const std::string& filePath, YAML::Node& root);
YAML::Node readFileYaml(const std::string& filePath);
std::vector<std::string> getFileNamesInDirectory(const std::string directoryPath);


#endif // UTILS_H
