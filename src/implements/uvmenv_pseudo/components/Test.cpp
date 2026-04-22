#include <iostream>
#include <yaml-cpp/yaml.h>
#include "../../../headers/functions/utils.h"
#include "../../../headers/uvmenv_preudo/components/Test.h"
using namespace std;


void Test::addEnvironment(Environment* e) { 
    environments.push_back(e); 
}

vector<Environment*> Test::getEnvironments() { 
    return environments; 
}

void Test::setName(const string& name){
    this->name = name;
}

void Test::writeToTree(){
    // 1. Cargar el archivo original
    YAML::Node treeFile = readFileYaml(PROJECT_DIR + PATH_SEP + ".ptree.yml");

    // 2. Crear el nodo del test individual
    YAML::Node nuevoTest;
    nuevoTest["name"] = name;

    // 3. Construir la jerarquía: top -> tests -> [nuevoTest]
    // Usamos push_back para que 'tests' sea una lista (secuencia)
    treeFile["top"]["tests"].push_back(nuevoTest);

    // 4. Guardar el archivo original ya modificado
    writeFileYaml(".ptree.yml", treeFile);
}

// @Override
void Test::copyBaseFile(){
    cout << "Copiar archivo base de [component] " << basefilePath << " a " << uvmenvProjectDir << endl;
    filesystem::create_directory(uvmenvProjectDir + PATH_SEP + name);
    filesystem::copy(
        basefilePath, 
        uvmenvProjectDir + PATH_SEP + name + PATH_SEP + PYMODULE
    );
    cout << "Copiar base del Top" << endl;
}


// private
ComponentRegister<Test> Test::reg("Test");


