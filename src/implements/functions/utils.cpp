#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <array>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>

#include "../../headers/functions/constants.h"
#include "../../headers/functions/utils.h"
using json = nlohmann::ordered_json;
namespace fs = std::filesystem;
using namespace std;



// ****************** INTERFACE UTIL FUNCTIONS ****************** //
void print(std::string message){
    cout << message << endl;
}
void printError(string message){
    cout << C_RED << message << C_N << endl;
}

void printInfo(string message){
    cout << C_GREEN << message << C_N << endl;
}

void printWarning(string message){
    cout << C_YELLOW << message << C_N << endl;
}

void printOption(string option, string message){
    cout << "     " << C_CYAN << option << C_N << "\n\t" << message << endl;
}

int countCharOcurrences(char c, string str) {
    int count = 0;

    for (char i : str)
        if (i == c) count++;

    return count;
}

vector<string> splitString(const string& input, char delimiter) {
    vector<string> tokens;
    istringstream stream(input);
    string token;

    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string trim(const string& s){
    // Look for the first character different to whithe space
    size_t first = s.find_first_not_of(WHITESPACE);
    
    // Not found => is all empty, so return empty
    if (first == string::npos) 
        return "";
    
    // Look for the last character different to whithe space
    size_t last = s.find_last_not_of(WHITESPACE);
    
    return s.substr(first, (last - first + 1));
}

string doTabs(const int& n) {
    if(n<=1) return TAB;
    
    string retTabs = "";
    for(int i=0; i<n; i++)
        retTabs += TAB;

    return retTabs;
}

// void replaceAll(string& str, const string& from, const string& to){
//     size_t pos = 0;

//     while ((pos = str.find(from, pos)) != string::npos)
//     {
//         str.replace(pos, from.length(), to);
//         pos += to.length();
//     }
// }

bool isPascalCase(const string& s) {
    if (s.empty()) return true;
    
    // Regla 1: La primera letra debe ser mayúscula
    if (!isupper(static_cast<unsigned char>(s[0]))) return false;

    for (size_t i = 0; i < s.length(); ++i) {
        unsigned char c = s[i];
        // Regla 2: No debe contener espacios
        if (isspace(c)) return false;

        // Regla 3: Si hay una mayúscula después de la primera posición,
        // debe ser precedida por una minúscula o número (evita ABCCase)
        // Nota: Esta regla es opcional dependiendo de qué tan estricto quieras ser.
    }
    return true;
}

string toPascalCase(const string& texto) {
    // Si ya está en PascalCase, devolvemos el original intacto
    if (isPascalCase(texto)) {
        return texto;
    }

    string resultado;
    bool proximaMayuscula = true;

    for (unsigned char c : texto) {
        if (isspace(c) || c == '_' || c == '-') { // Añadimos soporte para snake_case y kebab-case
            proximaMayuscula = true;
        } else {
            if (proximaMayuscula) {
                resultado += (char)toupper(c);
                proximaMayuscula = false;
            } else {
                resultado += (char)tolower(c);
            }
        }
    }

    return resultado;
}

bool isSnakeCase(const string& s) {
    if (s.empty()) return true;

    // Regla 1: No debe empezar ni terminar con guion bajo
    if (s.front() == '_' || s.back() == '_') return false;

    for (size_t i = 0; i < s.length(); ++i) {
        unsigned char c = s[i];

        // Regla 2: Solo minúsculas, números o guiones bajos
        if (!islower(c) && !isdigit(c) && c != '_') {
            return false;
        }

        // Regla 3: Evitar guiones bajos dobles (opcional pero recomendado)
        if (c == '_' && i + 1 < s.length() && s[i + 1] == '_') {
            return false;
        }
    }
    return true;
}

string toSnakeCase(const string& texto) {
    // Si ya cumple el formato, devolvemos el original
    if (isSnakeCase(texto)) {
        return texto;
    }

    string resultado;
    for (size_t i = 0; i < texto.length(); ++i) {
        unsigned char c = texto[i];

        if (isspace(c) || c == '-') {
            // Convertimos espacios o guiones de kebab-case a snake_case
            if (!resultado.empty() && resultado.back() != '_') {
                resultado += '_';
            }
        } else if (isupper(c)) {
            // Si es mayúscula y no es el inicio, añadimos guion (PascalCase/camelCase)
            if (!resultado.empty() && resultado.back() != '_') {
                resultado += '_';
            }
            resultado += (char)tolower(c);
        } else if (c == '_') {
            // Evitamos duplicar guiones bajos si ya vienen en el input
            if (!resultado.empty() && resultado.back() != '_') {
                resultado += '_';
            }
        } else {
            resultado += c;
        }
    }

    // Limpieza final: eliminar guion bajo al final si quedó uno por un espacio extra
    if (!resultado.empty() && resultado.back() == '_') {
        resultado.pop_back();
    }

    return resultado;
}

bool isInOptions(const string& value, const vector<string>* options) {
    // 1. Verify options pointer is valid
    if (options == nullptr) {
        return false;
    }

    // 2. Look for element. 
    // find  returns an iterator to the element if it is found 
    // or the iterator 'end()' if not.
    auto it = find(options->begin(), options->end(), value);

    // 3. Return true if iterator did not comes to end
    return it != options->end();
}
////////////////////////////////////////////////////////////////////



// ****************** Base 64 ****************** //
string base64_encode(const string &in) {
    static const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string out;
    int val = 0, valb = -6;

    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    return out;
}


string base64_decode(const string &in) {
    static const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[chars[i]] = i;

    string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}
///////////////////////////////////////////////////////////////////


// ***************** File writing/reading/research ***************** //
void writeFile(const string filePath, const string content) {
    ofstream outFile(filePath);
    if (!outFile) {
        printError("Error opening file for writing: " + filePath);
        return;
    }
    outFile << content;
    outFile.close();
}

string readFile(const string filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        printError("Error opening file for reading: " + filePath);
        return "";
    }
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return content;
}

void writeFileJson(const string& filePath, const json& jsonData) {
    ofstream file(filePath);
    fs::path p(filePath);

    if (!file.is_open()) {
        throw runtime_error("Could not open JSON file ("+p.filename().string()+") for writing: " + filePath);
    }

    file << jsonData.dump(4); // Pretty print with 4 spaces indentation
    file.close();
}

json readFileJson(const string& filePath) {
    ifstream file(filePath);
    fs::path p(filePath);

    if (!file.is_open()) {
        throw runtime_error("Could not open JSON file ("+p.filename().string()+"): " + filePath);
    }
    // json jsonData;
    // file >> jsonData;
    // return jsonData;
    return json::parse(file);
}

void writeFileYaml(const std::string& filePath, YAML::Node& root) {
    std::ofstream file(filePath);
    fs::path p(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open YAML file (" + p.filename().string() + ") for writing: " + filePath);
    }

    // 1. Creamos un Emitter
    YAML::Emitter emitter;

    // 2. Configuramos la indentación a 4 espacios
    emitter.SetIndent(4);
    
    // Opcional: Esto ayuda a que las secuencias (listas) también respeten la indentación
    emitter.SetSeqFormat(YAML::Block); 

    // 3. Pasamos el nodo al emitter
    emitter << root;

    // 4. Escribimos el contenido del emitter en el archivo
    file << emitter.c_str();
    
    file.close();
}

YAML::Node readFileYaml(const string& filePath){
    ifstream file(filePath);
    fs::path p(filePath);

    if (!file.is_open()) {
        throw runtime_error("Could not open YAML file (" + p.filename().string() + "): " + filePath);
    }

    return YAML::LoadFile(filePath);
}

vector<string> getFileNamesInDirectory(const string directoryPath) {
    vector<string> fileNames;

    try {
        for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                fileNames.push_back(entry.path().filename().string());
            } else if (entry.is_directory()) {
                // Get internal files recursively
                vector<string> subFiles = getFileNamesInDirectory(entry.path().string());
                for (const auto& subFile : subFiles) {
                    fileNames.push_back(entry.path().filename().string() + "/" + subFile);
                }
            }
        }
    } catch (const filesystem::filesystem_error& e) {
        cerr << "Error accediendo al directorio: " << e.what() << endl;
    }

    return fileNames;
}
///////////////////////////////////////////////////////////////////


