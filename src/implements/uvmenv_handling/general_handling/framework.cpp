#include <string>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <array>
#include <fstream>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

#include "../../../headers/uvmenv_preudo/components/Top.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"

using namespace std;
using json = nlohmann::ordered_json;
namespace py = pybind11;

// ===========================================================
// Block to expose C++ to Python embedded instance
// ===========================================================
PYBIND11_EMBEDDED_MODULE(signalsGetter, m) {
    py::class_<Signal>(m, "Signal")
        .def(py::init<>()) // Constructor por defecto
        .def(py::init<string, string, int>()) // Constructor personalizado (opcional pero recomendado)
        .def_readwrite("name", &Signal::name)
        .def_readwrite("type", &Signal::type)
        .def_readwrite("size", &Signal::size);
}
// ===========================================================


bool isUVMEnvProject(const string& path){
    vector<string> pdirParts = splitString( path, PATH_SEP.at(0) );
    string projectIdExpected = "uvm:" + pdirParts[pdirParts.size()-1] + ":env";
    string configFileName = joinStr({path, "config.json"}, PATH_SEP);

    
    if( !filesystem::exists(configFileName) ){
        return false;
    }

    ifstream config_file(configFileName);
    json configFileData = json::parse(config_file);
    
    return base64_decode( configFileData["id"] ) == projectIdExpected;
} 


bool existsDUT(){
    string rtlFiles = execCmdReturn(getScript("sys_commands") + "getRTLModuleNames " + DUT_HDL_DIR);
    return trim(rtlFiles) != "";
}

void showProjectTree(){
    execCmdSimple(getScript("sys_commands")+"viewTreeProject");
}

void showReport(){
    execCmdSimple(getScript("sys_commands")+"viewReport " + OUTSIM_DIR);
}

void showWaveform(){
    execCmdSimple(getScript("sys_commands")+"runGTKWave " + OUTSIM_DIR);
}


void showHelp() {
    const int w = 15;
    cout << "Usage:\t uvmenv COMMAND OPTION <COMPONENT> <PARAMETERS> " << endl;

    cout << endl;

    cout << "COMMAND is mandatory." << endl;
    cout << "OPTION is required by COMMAND \"project\" and \"component\"." << endl;
    cout << "COMPONENT is required when COMMAND is \"component\"." << endl;
    cout << "PARAMETERS are required depending on the OPTION and COMPONENT." << endl;

    cout << endl;

    cout << "COMMAND" << endl;
    cout << left; // Alineación a la izquierda para el comando
    cout << "    " << setw(w) << "new"       << "Create a new UVMEnv project." << endl;
    cout << "    " << setw(w) << "search"    << "Look for UVMEnv projects into current directory." << endl;
    cout << "    " << setw(w) << "help"      << "Show this help." << endl;
    cout << "    " << setw(w) << "project"   << "Manage current project." << endl;
    cout << "    " << setw(w) << "component" << "Manage UVM components of current project." << endl;

    cout << endl;

    cout << "OPTION" << endl;
    cout << "For \"project\"" << endl;
    cout << "    " << setw(w) << "init"      << "Create default structure with only one test and environment." << endl;
    cout << "    " << setw(w) << "view"      << "Shows project tree." << endl;
    cout << "    " << setw(w) << "run"       << "Starts verification process." << endl;
    cout << "    " << setw(w) << "wave"      << "Shows waveform." << endl;
    cout << "    " << setw(w) << "report"    << "Shows the report file content." << endl;
    cout << "For \"component\"" << endl;
    cout << "    " << setw(w) << "create"    << "Create a UVM component." << endl;
    cout << "    " << setw(w) << "edit"      << "Allow to edit each file of current UVMEnv project." << endl;
    cout << "    " << setw(w) << "delete"    << "Delete a UVM component." << endl;
    cout << "    " << setw(w) << "list"      << "List UVM components and RTL modules and signals." << endl;

    cout << endl;

    cout << "COMPONENT:" << endl;

    cout << endl;

    cout << "PARAMETERS:" << endl;

    cout << endl;
}


void createNewEnv(const string& projectName, const string& topModule){
    if(filesystem::exists(PROJECT_DIR + PATH_SEP + projectName)){
        printError("The UVMEnv project " + projectName + " already exists. Please choose another name.");
        return;
    }

    // Create directories structure
    filesystem::create_directory(PROJECT_DIR + PATH_SEP + projectName);
    filesystem::current_path(PROJECT_DIR + PATH_SEP + projectName);

    // Create UVMenv structure directories
    filesystem::create_directory("HDLSrc");
    filesystem::create_directory("OSimon");
    filesystem::create_directories("Itface" + PATH_SEP + "_impl");
    filesystem::copy(
        BASES_COMPONENT_DIR + PATH_SEP + "BFMBase.py",
        "Itface" + PATH_SEP + "BFM.py"
    );
    filesystem::create_directory("UVM_TB");
    //// filesystem::create_directories("UVM_TB" + PATH_SEP + "SeqItm");
    //// filesystem::create_directories("UVM_TB" + PATH_SEP + "Seqnce");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt");
    //// filesystem::create_directories("UVM_TB" + PATH_SEP + "Misces");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "Scorbd");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "Agents");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "RefMdl" + PATH_SEP + "_impl");

    // Create config file
    json configContent;
    configContent["id"] = base64_encode("uvm:" + projectName + ":env");
    configContent["name"] = projectName;
    configContent["simtool"] = "icarus";
    configContent["dut_design"] = {
        {"type", "combinatorial"},
        {"top_module", topModule},
        {"sync_clock_cycles", "1"}
    };
    configContent["uvm_components"] = {
        {"itface", {
            {"bfm_impl", "DefaultBfmImpl"}
        }},
        {"refmdl", {
            {"refmdl_impl", "DefaultRefModelImpl"}
        }}
    };
    writeFileJson("config.json", configContent);

    // Create project tree file
    YAML::Node topNode;
    topNode["top"]["tests"] = YAML::Null;
    topNode["top"]["itfaces"] = YAML::Null;
    writeFileYaml(".ptree.yml", topNode);



    // Create UVMenv structure files - Make each manager of UVM level
    ////// Write script of utils
    filesystem::copy(UTIL_FILEBASE, "utils.py");

    ////// Write script of paths
    filesystem::copy(PATHS_FILEBASE, "paths.py");

    ////// Write Top
    UVMComponent* top = &Top::instance();
    Top::instance().setProjectName(projectName);
    Top::instance().setTopModuleName(topModule);
    top -> copyBaseFile();
    //filesystem::copy(TOP_FILEBASE, "Top_"+topModule+".py");

    ////// Write Test
    //filesystem::copy(TEST_FILEBASE, "UVM_TB/Test.py");

    ////// Write Environment
    //filesystem::copy(ENVIRONMENT_FILEBASE, "UVM_TB/Envmnt/Environment.py");

    ////// Write interface for BFM
    //// filesystem::copy(BFM_FILEBASE, "Itface" + PATH_SEP + "BFM.py");

    ////// Write interface for Reference model
    //filesystem::copy(REFMODEL_FILEBASE, "UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "RefMdl/RefModel.py");

    ////// Write report mechanism
    //// filesystem::copy(REPORT_FILEBASE, "UVM_TB" + PATH_SEP + "Misces" + PATH_SEP + "UVMEnvReport.py");

    filesystem::current_path(PROJECT_DIR);
}


void runCurrentProject(){
    string rtlFiles = execCmdReturn(getScript("sys_commands") + "getRTLFullFiles " + DUT_HDL_DIR);
    string pyVersion = getPythonVersion();

    // Leer el archivo de configuración JSON
    ifstream f(CONFIG_FILE);
    json config = json::parse(f);

    // Extraer valores del JSON (equivalente a jq)
    string simtool = config.value("simtool", "icarus");
    string top_module = config["dut_design"].value("top_module", "unknown");

    // Crear/Sobrescribir el archivo Makefile
    ofstream makefile("Makefile");

    if (makefile.is_open()) {
        makefile << "CWD = $(shell pwd)\n";
        makefile << "HDL_SRC = " << simtool << "\n";
        makefile << "SIM ?= " << simtool << "\n";
        makefile << "\n\n";
        
        makefile << "VERILOG_SOURCES = " << rtlFiles << "\n";
        makefile << "\n\n";
        
        makefile << "MODULE = Top_" << top_module << "\n";
        makefile << "TOPLEVEL = " << top_module << "\n";
        makefile << "TOPLEVEL_LANG ?= verilog\n";
        //makefile << (   stof(pyVersion) >= 3.11 ? VENV_DIR + PATH_SEP + "bin" + PATH_SEP + "python" + pyVersion : "python"+pyVersion   );
        makefile << "#COCOTB_HDL_TIMEOUT = 1ns\n";
        makefile << "#COCOTB_HDL_TIMEPRECISION = 1ns\n";
        makefile << "\n\n";
        
        makefile << "include $(shell cocotb-config --makefiles)/Makefile.sim\n";
        makefile << "\n";

        makefile.close();
    } else {
        cerr << "Error: Impossible to create Makefile." << endl;
    }

    execCmdSimple(getScript("python_control") + "runUVMEnvProject " + PROJECT_DIR + " " + pyVersion);
    execCmdSimple(getScript("sys_commands") + "cleanProject " + PROJECT_DIR);
}


void searchProjects(){
    vector<string> projects;

    for (const auto& entry : filesystem::directory_iterator(PROJECT_DIR)) {
        if (filesystem::is_directory(entry.status())) {
            if( isUVMEnvProject(entry.path()) ){
                projects.push_back(entry.path().filename());
            }
            filesystem::current_path(PROJECT_DIR);
        } 
    }

    for(const auto& name: projects)
        cout << name << endl;
}


// @arg option: 'r' for refresh and 'n' for normal options 
 unordered_map<string, vector<Signal>> getDUTSignals(const char& option){
    unordered_map<string, vector<Signal>> dutSignals;
    if(!existsDUT()){
        printWarning("No RTL files found in " + DUT_HDL_DIR + " directory. Please, add your RTL source into HDLSrc");
        return dutSignals;
    }

    const string& rtlFullFiles = trim( execCmdReturn(getScript("sys_commands") + "getRTLFullFiles " + DUT_HDL_DIR) );
    const string& rtlModuleNames = trim( execCmdReturn(getScript("sys_commands") + "getRTLModuleNames " + DUT_HDL_DIR) );

    string auxDir = DUT_HDL_DIR + PATH_SEP + "auxHDL";
    // Let's consider append option by default
    char writeOption = 'a';
    int count = 0;


    // ==================================================================
    // Initialize Python interpreter and add auxDir to Python path
    // ==================================================================
    // This block is necesarry to correct work of runSignalsGetter
    static py::scoped_interpreter guard{};

    py::module_ sys = py::module_::import("sys");
    sys.attr("path").attr("append")(auxDir.c_str());
    // ==================================================================

    
    // ==================================================================
    // If option is refresh, let's generate a new .allSignalsFie.csv
    // ==================================================================
    if(option == 'r'){
        filesystem::remove(DUT_HDL_DIR + PATH_SEP + ".allSignals.csv");

        // Make the auxiliar directory and copy files of DUT
        filesystem::create_directory(auxDir);
        for(const string& m: splitString(rtlFullFiles, ' ')){
            filesystem::copy(m, auxDir);
        }
        
        // Copy the base fiel of signals getter into aux signals.py
        filesystem::copy(SIGNAL_GETTER_FILEBASE, auxDir + PATH_SEP + "signals.py");

        // Verilate each module into the aux directory
        filesystem::current_path(auxDir);
        for(const string& mod: splitString(rtlModuleNames, ' ')){
            if(count > 0)
                writeOption = 'a';
            else
                writeOption = 'w';
            execCmdSimple(joinStr(
                {getScript("sys_commands")+" verilateModel", mod},
                " "
            ));

            runSignalsGetter(mod, writeOption, option);
            count++;
        }
        filesystem::copy(".allSignals.csv", DUT_HDL_DIR);
        count = 0;
        filesystem::current_path(PROJECT_DIR);
        filesystem::remove_all(auxDir);
    } // End if option is r
    // ==================================================================


    // ==================================================================
    // Always read from .csv file
    // ==================================================================
    filesystem::current_path(DUT_HDL_DIR);
    
    // Copy signals getter file
    if( !filesystem::exists("signals.py") )
        filesystem::copy(SIGNAL_GETTER_FILEBASE, "signals.py");
    
    for(const string& mod: splitString(rtlModuleNames, ' ')){
        dutSignals[mod] = runSignalsGetter(mod, 'x', 'n');
    }

    filesystem::remove("signals.py");
    filesystem::current_path(PROJECT_DIR);

    return dutSignals;
    // ==================================================================
}

void printDUTSignals(const unordered_map<string, vector<Signal>>& dutSignals){
    for(const auto& [mod, signals]: dutSignals){
        printInfo("\tSignals of " + mod);
        for(const auto& sig: signals){
            print(sig.type + "[" + to_string(sig.size) + " bit]: " + sig.name);
        }
    }
}






bool requireProject(){
    if(!isUVMEnvProject(PROJECT_DIR)){
        printError("You need using a valid project to run this option.");
        return false;
    }
    return true;
}

bool requireDUT(){
    if(!existsDUT()){
        printError("DUT files not found.");
        return false;
    }
    return true;
}

bool requireArgs(initializer_list<string> args, const string& msg){
    for (const auto& arg : args) {
        if (arg.empty()) {
            printWarning(msg);
            return false;
        }
    }
    return true;
}


vector<Signal> runSignalsGetter(const string& module, char writeOption, char option){
    try{
        py::module_ LeyendoPy = py::module_::import("signals");

        py::object resultado = LeyendoPy.attr("get_signals")("obj_dir/V"+module+".h", writeOption, option);

        std::vector<Signal> signals = resultado.cast<std::vector<Signal>>();

        return signals;

    } catch (py::error_already_set &e) {
        std::cerr << "[Error de Python] " << e.what() << std::endl;
        return {};
    }
}



