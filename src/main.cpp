#include "headers/functions/utils.h"
#include "headers/functions/constants.h"
#include "headers/functions/ptree_handling.h"

#include "headers/uvmenv_handling/component_handling/create_component.h" ///
#include "headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "headers/uvmenv_handling/general_handling/framework.h"

#include "headers/uvmenv_preudo/Factory.h"
#include "headers/uvmenv_preudo/components/Top.h"
#include "headers/uvmenv_preudo/UVMObject.h"
#include "headers/uvmenv_preudo/UVMComponent.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <typeinfo>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>
using namespace std;
using json = nlohmann::json;

// NOTE: Include sudo apt install nlohmann-json3-dev on install script.

void uvm_factory_test();
void json_handling_test();
void yml_handling_test();
void genYamlUVMEnv();
void test_handling_yaml(char *args[]);
void component_creation_test();


int main (int argc, char *argv[]) {
    cout << C_GREEN << "UVMEnv 2.0 - TESTING/DEVELOPING" << C_N << endl;
    if(argc < 2) {
        showHelp();
        return 0;
    }

    string option = argv[1];
    
    ///// FRAMEWORK HANDLING /////
    if(option == "new") {

        if(argv[2] == nullptr || argv[3] == nullptr){
            printError("Missing parameters");
            printInfo("Usage: uvmenv -n|--new <project name> <top module name>");
            exit(0);
        }

        // argv[2]: Project name.
        // argv[3]: Top module name.
        createNewEnv(argv[2], argv[3]);
    } 
    else if(option == "search") {
        if(isUVMEnvProject(PROJECT_DIR)){
            printInfo("You are already into a UVMEnv project");
            return 0;
        }

        searchProjects();
    } 
    else if(option == "help") {
        showHelp();
    }

    ///// PROJECT HANDLING /////
    else if(option == "project"){
        if(!isUVMEnvProject(PROJECT_DIR)){
            printError("You need using a valid project to run this option.");
            return 1;
        }

        if(argv[2] == nullptr){
            printError("Missing project option");
            return 4;
        }

        
        if(string(argv[2]) == "view"){
            showProjectTree();
        }
        else if(string(argv[2]) == "init"){
            cout << "Initializing project..." << endl;
        }
        else if(string(argv[2]) == "report"){
            showReport();
        }
        else if(string(argv[2]) == "wave"){
            cout << "Show waveform..." << endl;
            //showWaveform();
        }
        else if(string(argv[2]) == "run"){
            if(!existsDUT()){
                printError("DUT files not found.");
                return 3;
            }
            runCurrentProject();
        }
        else {
            printError("Unknown project option: " + string(argv[2]));
            return 2;
        }
    }
    
    ///// COMPONENT HANDLING /////
    else if(option == "component"){
        if(!isUVMEnvProject(PROJECT_DIR)){
            printError("You need using a valid project to run this option.");
            return 1;
        }

        if(argv[2] == nullptr){
            printError("USAGE: uvmenv component OPTION COMPONENT ATTRIBUTES");
            printInfo("See uvmenv help for more details");
            return 4;
        }

        if(argv[3] == nullptr){
            printError("Missing component reference");
            return 4;
        }
        else{
            // Validate component existence 
            cout << "Validate component existence" << endl;
        }

        
        if(string(argv[2]) == "create"){
            cout << "Creating component..." << endl;
            cout << "Component type: " << argv[3] << endl;
            if(string(argv[3]) == "test"){
                if(argv[4] == nullptr){
                    printError("Missing component name");
                    return 4;
                }
                createTest(argv[4]);
            }
            //createAgent("Agent_A1", "driver", "Driver_A1", nullptr);
            //createAgent("Agent_A1", "driver", "Driver_A1", nullptr);
        }
        else if(string(argv[2]) == "delete"){

        }
        else if(string(argv[2]) == "edit"){
            
        }
        else if(string(argv[2]) == "list"){
            
        }
        else {
            printError("Unknown component option: " + string(argv[2]));
            return 2;
        }
        
    }

    else if(option == "test") {
        component_creation_test();
    }

    else {
        printError("Unknown option: " + option);
        return 2;
    }

    return 0;
}




// ==============
// TESTS
// ==============
void component_creation_test(){
    createBFM("spike");
    createBFM("otro simulador");
    createBFM("python model");

    createTest("new test");
    createSequence("new sequence", "TestNewTest");
    createSeqitem("el seqitem", "TestNewTest");  
    createTest("otro test");
    createSequence("otra secuencia", "TestOtroTest");
    createSeqitem("otro seqitem", "TestOtroTest");

    createEnvironmentOnTest("env de prueba", "TestNewTest");
    createEnvironmentOnTest("env de prueba2", "TestNewTest");

    createRefModel("model de prueba", "EnvEnvDePrueba", "TestNewTest");
    createRefModel("equis de", "EnvEnvDePrueba", "TestNewTest");
    createRefModel("pichula", "EnvEnvDePrueba2", "TestNewTest");
    createRefModel("otra pichula", "EnvEnvDePrueba2", "TestNewTest");

    createAgent("agent de prueba", "EnvEnvDePrueba", "TestNewTest");
    createAgent("uart", "EnvEnvDePrueba", "TestNewTest");

    createScoreboard("prueba", "EnvEnvDePrueba", "TestNewTest");
    createScoreboard("prueba2", "EnvEnvDePrueba", "TestNewTest");
}

void test_handling_yaml(char *args[]){
    if(string(args[2]) == "test") {
        if(string(args[3]) == "a")
            treeAddTest(args[4]);
        else
            treeDeleteTest(args[4]);
        for(const auto& t : treeListTest()) cout << "\t" << t << endl;
    }
    else if(string(args[2]) == "bfm"){
        if(string(args[3]) == "a")
            treeAddInterface(args[4]);
        else
            treeDeleteInterface(args[4]);
        for(const auto& t : treeListInterface()) cout << "\t" << t << endl;
    }
    else if(string(args[2]) == "seqitem"){
        if(string(args[3]) == "a")
            treeAddSeqitem(args[4], args[5]);
        else
            treeDeleteSeqitem(args[4], args[5]);
        for(const auto& t : treeListSeqitem(args[5])) cout << "\t" << t << endl;
    }
    else if(string(args[2]) == "sequence"){
        if(string(args[3]) == "a")
            treeAddSequences(args[4], args[5]);
        else
            treeDeleteSequences(args[4], args[5]);
        for(const auto& t : treeListSequences(args[5])) cout << "\t" << t << endl;
    }
    else if(string(args[2]) == "env"){
        if(string(args[3]) == "a")
            treeAddEnvironment(args[4], args[5]);
        else
            treeDeleteEnvironment(args[4], args[5]);
        for(const auto& t : treeListEnvironments(args[5])) cout << "\t" << t << endl;
    }
    else if(string(args[2]) == "rmod"){
        if(string(args[3]) == "a")
            treeAddRefmodel(args[4], args[5], args[6]);
        else
            treeDeleteRefmodel(args[4], args[5], args[6]);
        for(const auto& t : treeListRefmodel(args[5], args[6])) cout << "\t" << t << endl;
    }
    else if(string(args[2]) == "agent"){
        if(string(args[3]) == "a")
            treeAddAgent(args[4], args[5], args[6]);
        else
            treeDeleteAgent(args[4], args[5], args[6]);
        for(const auto& t : treeListAgents(args[5], args[6])) cout << "\t" << t << endl;
    }
    else if(string(args[2]) == "scoreboard"){
        if(string(args[3]) == "a")
            treeAddScoreboard(args[4], args[5], args[6]);
        else
            treeDeleteScoreboard(args[4], args[5], args[6]);
        for(const auto& t : treeListScoreboards(args[5], args[6])) cout << "\t" << t << endl;
    }
}

void genYamlUVMEnv() {
    YAML::Node topNode;

    // --- 1. Sección bfm ---
    YAML::Node bfm;
    bfm["bfm"].push_back("BfmAbcd1");
    bfm["bfm"].push_back("BfmAbcd2");
    bfm["bfm"].push_back("BfmAbcd3");
    bfm["bfm"].push_back("BfmAbcd4");
    topNode["top"].push_back(bfm);

    // --- 2. Preparar la estructura de los ENVS comunes ---
    auto crearEnv = []() {
        YAML::Node env;
        env["name"] = "EnvAbcd";
        
        env["refmodels"].push_back("RmSpike");
        env["refmodels"].push_back("RmImperas");
        env["refmodels"].push_back("RmVerilator");

        env["agents"].push_back("AgentAbcd1");
        env["agents"].push_back("AgentAbcd2");
        env["agents"].push_back("AgentAbcd3");

        env["scoreboards"].push_back("ScbdAbcd1");
        env["scoreboards"].push_back("ScbdAbcd2");
        env["scoreboards"].push_back("ScbdAbcd3");
        return env;
    };

    // --- 3. Sección tests ---
    YAML::Node testsSection;
    
    // Test 1: Tiene 1 Env
    YAML::Node test1;
    test1["name"] = "";
    test1["seqitems"].push_back("SitmPrueba1");
    test1["seqitems"].push_back("SitmPrueba2");
    test1["seqitems"].push_back("SitmPrueba3");
    test1["sequences"].push_back("SeqPrueba1");
    test1["sequences"].push_back("SeqPrueba2");
    test1["sequences"].push_back("SeqPrueba3");
    test1["envs"].push_back(crearEnv());

    // Test 2: Tiene 2 Envs (según tu última actualización)
    YAML::Node test2;
    test2["name"] = "";
    test2["seqitems"].push_back("SitmPrueba1");
    test2["seqitems"].push_back("SitmPrueba2");
    test2["seqitems"].push_back("SitmPrueba3");
    test2["sequences"].push_back("SeqPrueba1");
    test2["sequences"].push_back("SeqPrueba2");
    test2["sequences"].push_back("SeqPrueba3");
    test2["envs"].push_back(crearEnv());
    test2["envs"].push_back(crearEnv());

    // Añadir ambos tests a la sección de tests
    YAML::Node testsWrapper;
    testsWrapper["tests"].push_back(test1);
    testsWrapper["tests"].push_back(test2);

    topNode["top"].push_back(testsWrapper);

    // --- 4. Escritura a archivo ---
    std::ofstream fout("config_verif.yml");
    fout << topNode;
    fout.close();

    std::cout << "Archivo .yml generado exitosamente." << std::endl;
}

void yml_handling_test()
{
    string dictComponents = PROJECT_DIR + PATH_SEP + "project_tree.yml";

    YAML::Node y;

    // --- Llenamos las listas simples ---
    y["seqitems"].push_back("SitmPrueba1");
    y["seqitems"].push_back("SitmPrueba2");
    y["seqitems"].push_back("SitmPrueba3");

    y["sequences"].push_back("SeqPrueba1");
    y["sequences"].push_back("SeqPrueba2");
    y["sequences"].push_back("SeqPrueba3");

    y["refmodels"].push_back("RmSpike");
    y["refmodels"].push_back("RmImperas");
    y["refmodels"].push_back("RmVerilator");

    // --- Creamos el objeto interno para "envs" ---
    YAML::Node env;
    env["name"] = "EnvAbcd";
    env["agents"].push_back("AgentAbcd1");
    env["agents"].push_back("AgentAbcd2");
    env["agents"].push_back("AgentAbcd3");

    env["scoreboards"].push_back("ScbdAbcd1");
    env["scoreboards"].push_back("ScbdAbcd2");
    env["scoreboards"].push_back("ScbdAbcd3");

    // --- Creamos el objeto test ---
    YAML::Node test;
    test["name"] = "";
    test["envs"].push_back(env);

    y["tests"].push_back(test);

    writeFileYaml(dictComponents, y);

    // -------- LECTURA --------
    YAML::Node treef = readFileYaml(dictComponents);

    cout << treef["tests"][0]["envs"][0]["agents"] << endl;

    for (const auto& g : treef["tests"][0]["envs"][0]["agents"])
    {
        cout << g.as<string>() << endl;
    }

    // ---------------- OPERACIONES ----------------

    // 1. Agregar un agente nuevo al primer env del primer test
    y["tests"][0]["envs"][0]["agents"].push_back("Agent_EXTRA");

    // 2. Eliminar "SitmPrueba2" de la lista seqitems
    YAML::Node nuevaSeq;
    for (const auto& item : y["seqitems"])
    {
        if (item.as<string>() != "SitmPrueba2")
            nuevaSeq.push_back(item);
    }
    y["seqitems"] = nuevaSeq;

    // 3. Crear un nuevo test completo y añadirlo al array
    YAML::Node nuevo_test;
    nuevo_test["name"] = "TestSecundario";
    nuevo_test["envs"] = YAML::Node(YAML::NodeType::Sequence);

    y["tests"].push_back(nuevo_test);

    // 4. Eliminar el nombre del primer env (la llave completa)
    y["tests"][0]["envs"][0].remove("name");

    writeFileYaml(dictComponents + ".yml", y);
}

void json_handling_test(){
    string dictComponents = PROJECT_DIR + PATH_SEP + "project_tree.json"; // Make it hidden file in the future

    json j;
    // Llenamos las listas simples
    j["seqitems"] = {"SitmPrueba1", "SitmPrueba2", "SitmPrueba3"};
    j["sequences"] = {"SeqPrueba1", "SeqPrueba2", "SeqPrueba3"};
    j["refmodels"] = {"RmSpike", "RmImperas", "RmVerilator"};

    // Creamos el objeto interno para "envs"
    json env;
    env["name"] = "EnvAbcd";
    env["agents"] = {"AgentAbcd1", "AgentAbcd2", "AgentAbcd3"};
    env["scoreboards"] = {"ScbdAbcd1", "ScbdAbcd2", "ScbdAbcd3"};

    // Creamos el objeto del nodo principal (con nombre vacío según tu ejemplo)
    json test;
    test["name"] = "";
    test["envs"] = {env}; // Metemos el env dentro de un arreglo

    // Finalmente asignamos el arreglo de objetos a una llave (ejemplo: "nodes")
    j["tests"] = {test};

    writeFileJson(dictComponents, j);

    // LECTURA
    json treef = readFileJson(dictComponents);
    cout << treef["tests"][0]["envs"][0]["agents"] << endl;
    for(string g: treef["tests"][0]["envs"][0]["agents"]){
        cout << g << endl;
    }


    // --- OPERACIONES ---

    // 1. Agregar un agente nuevo al primer env del primer test
    j["tests"][0]["envs"][0]["agents"].push_back("Agent_EXTRA");

    // 2. Eliminar "SitmPrueba2" de la lista seqitems
    // Una forma rápida de borrar por valor en C++11+
    auto& s = j["seqitems"];
    for (auto it = s.begin(); it != s.end(); ) {
        if (*it == "SitmPrueba2") it = s.erase(it);
        else ++it;
    }

    // 3. Crear un nuevo 'test' completo y añadirlo al array de tests
    json nuevo_test = {{"name", "TestSecundario"}, {"envs", json::array()}};
    j["tests"].push_back(nuevo_test);

    // 4. Eliminar el nombre del primer env (la llave completa)
    j["tests"][0]["envs"][0].erase("name");

    writeFileJson(dictComponents+".json", j);
}

void uvm_factory_test(){
    UVMComponent* top = &Top::instance();


    //------------------------------------------------------
    // TEST 1
    //------------------------------------------------------
    UVMComponent* test1 = Factory::instance().createComponent("Test","Test_A",top);

    // Environments
    UVMComponent* env1 = Factory::instance().createComponent("Environment","Env_A1",test1);
    UVMComponent* env2 = Factory::instance().createComponent("Environment","Env_A2",test1);


    // ---- ENV A1 ----
    UVMComponent* agtA1 = Factory::instance().createComponent("Agent","Agent_A1",env1);

    UVMComponent* drvA1 = Factory::instance().createComponent("Driver","Driver_A1",agtA1);
    UVMComponent* monA1 = Factory::instance().createComponent("Monitor","Monitor_A1",agtA1);
    UVMComponent* covA1 = Factory::instance().createComponent("Coverage","Coverage_A1",agtA1);

    UVMComponent* scbA1 = Factory::instance().createComponent("Scoreboard","Scoreboard_A1",env1);


    // ---- ENV A2 ----
    UVMComponent* agtA2 = Factory::instance().createComponent("Agent","Agent_A2",env2);

    UVMComponent* drvA2 = Factory::instance().createComponent("Driver","Driver_A2",agtA2);
    UVMComponent* monA2 = Factory::instance().createComponent("Monitor","Monitor_A2",agtA2);
    UVMComponent* covA2 = Factory::instance().createComponent("Coverage","Coverage_A2",agtA2);

    UVMComponent* scbA2 = Factory::instance().createComponent("Scoreboard","Scoreboard_A2",env2);



    //------------------------------------------------------
    // TEST 2
    //------------------------------------------------------
    UVMComponent* test2 = Factory::instance().createComponent("Test","Test_B",top);

    // Environments
    UVMComponent* env3 = Factory::instance().createComponent("Environment","Env_B1",test2);
    UVMComponent* env4 = Factory::instance().createComponent("Environment","Env_B2",test2);

    // ---- ENV B1 ----
    UVMComponent* agtB1 = Factory::instance().createComponent("Agent","Agent_B1",env3);

    UVMComponent* drvB1 = Factory::instance().createComponent("Driver","Driver_B1",agtB1);
    UVMComponent* monB1 = Factory::instance().createComponent("Monitor","Monitor_B1",agtB1);
    UVMComponent* covB1 = Factory::instance().createComponent("Coverage","Coverage_B1",agtB1);

    UVMComponent* scbB1 = Factory::instance().createComponent("Scoreboard","Scoreboard_B1",env3);


    // ---- ENV B2 ----
    UVMComponent* agtB2 = Factory::instance().createComponent("Agent","Agent_B2",env4);

    UVMComponent* drvB2 = Factory::instance().createComponent("Driver","Driver_B2",agtB2);
    UVMComponent* monB2 = Factory::instance().createComponent("Monitor","Monitor_B2",agtB2);
    UVMComponent* covB2 = Factory::instance().createComponent("Coverage","Coverage_B2",agtB2);

    UVMComponent* scbB2 = Factory::instance().createComponent("Scoreboard","Scoreboard_B2",env4);



    //------------------------------------------------------
    // OBJECTS
    //------------------------------------------------------
    UVMObject* seqA = Factory::instance().createObject("Sequence","Seq_A");
    UVMObject* seqItemA = Factory::instance().createObject("SequenceItem","SeqItem_A");
    UVMObject* bfmA = Factory::instance().createObject("BFMImpl","BFM_A");
    UVMObject* refA = Factory::instance().createObject("RefModelImpl","RefModel_A");



    /********************************************************
     *
     * COPY BASEFILE
     *
     ********************************************************/

    top->copyBaseFile();
    test1->copyBaseFile();
    env1->copyBaseFile();
    env2->copyBaseFile();

    agtA1->copyBaseFile();
    drvA1->copyBaseFile();
    monA1->copyBaseFile();
    covA1->copyBaseFile();
    scbA1->copyBaseFile();

    agtA2->copyBaseFile();
    drvA2->copyBaseFile();
    monA2->copyBaseFile();
    covA2->copyBaseFile();
    scbA2->copyBaseFile();



    test2->copyBaseFile();
    env3->copyBaseFile();
    env4->copyBaseFile();

    agtB1->copyBaseFile();
    drvB1->copyBaseFile();
    monB1->copyBaseFile();
    covB1->copyBaseFile();
    scbB1->copyBaseFile();

    agtB2->copyBaseFile();
    drvB2->copyBaseFile();
    monB2->copyBaseFile();
    covB2->copyBaseFile();
    scbB2->copyBaseFile();


    // Objects

    seqA->copyBaseFile();
    seqItemA->copyBaseFile();
    bfmA->copyBaseFile();
    refA->copyBaseFile();



    /********************************************************
     *
     * PRINT TREE
     *
     ********************************************************/

    cout << top << endl;
    cout << test1 << endl;
    
    cout << env1 << endl;
    cout << agtA1 << endl;
    cout << drvA1 << endl;
    cout << monA1 << endl;
    cout << covA1 << endl;
    cout << scbA1 << endl;
    
    cout << env2 << endl;
    cout << agtA2 << endl;
    cout << drvA2 << endl;
    cout << monA2 << endl;
    cout << covA2 << endl;
    cout << scbA2 << endl;
    

    cout << test2 << endl;
    
    cout << env3 << endl;
    cout << agtB1 << endl;
    cout << drvB1 << endl;
    cout << monB1 << endl;
    cout << covB1 << endl;
    cout << scbB1 << endl;
    
    cout << env4 << endl;
    cout << agtB2 << endl;
    cout << drvB2 << endl;
    cout << monB2 << endl;
    cout << covB2 << endl;
    cout << scbB2 << endl;


    // Objects

    cout << seqA << endl;
    cout << seqItemA << endl;
    cout << bfmA << endl;
    cout << refA << endl;
}

