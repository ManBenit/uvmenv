#include <string>
#include <sstream>
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

#include "../../../headers/uvmenv_pseudo/components/Top.h"
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
// Inject module "signalsGetter" from C++ to Python, to be able to use Signal
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

void showCoverage(){
    execCmdSimple(getScript("sys_commands")+"viewCoverage " + OUTSIM_DIR);
}


void showHelp() {
    const int w = 15;
    stringstream helpMessage;
    helpMessage << "Usage:\t uvmenv <ctx> <opt> <comp> <name> [optional_args]" << "\n\n";

    helpMessage << "========== Positional arguments ==========" << "\n";
    helpMessage << "ctx (context): Current place to run an option." << "\n";
    helpMessage << "opt (option): Action to do into a context." << "\n";
    helpMessage << "comp (component): UVM component which will be handled." << "\n";
    helpMessage << "name (component name): Name of specific component for handling." << "\n";

    helpMessage << "\n";

    helpMessage << "========== Optional arguments ==========" << "\n";
    helpMessage << "--test: UVM test where component lives." << "\n";
    helpMessage << "--env: UVM env where component lives." << "\n";
    helpMessage << "--type: Type of agent for creation (std, psv, act, rct)." << "\n";
    helpMessage << "--wave-level: Wave level which will be rendered on GTKWave." << "\n";
    helpMessage << "--module: Some specific RTL module to create UVM classes." << "\n";

    helpMessage << "\n";

    helpMessage << "======= Values for ctx (context) =======" << "\n";
    helpMessage << left; // Alineación a la izquierda para el comando
    helpMessage << doTabs(1) << setw(w) << "new"       << "Create a new UVMEnv project." << "\n";
    helpMessage << doTabs(1) << setw(w) << "search"    << "Look for UVMEnv projects into current directory." << "\n";
    helpMessage << doTabs(1) << setw(w) << "help"      << "Show this help." << "\n";
    helpMessage << doTabs(1) << setw(w) << "project"   << "Manage current project." << "\n";
    helpMessage << doTabs(1) << setw(w) << "component" << "Manage UVM components of current project." << "\n";

    helpMessage << "\n";

    helpMessage << "======= Options \"project\" and \"component\" =======" << "\n";
    helpMessage << "For \"project\"" << "\n";
    helpMessage << doTabs(1) << setw(w) << "init"      << "Create default structure with only one test and environment." << "\n";
    helpMessage << doTabs(1) << setw(w) << "view"      << "Shows project tree." << "\n";
    helpMessage << doTabs(1) << setw(w) << "run"       << "Starts verification process. You can specify wave level with --wave-level option." << "\n";
    helpMessage << doTabs(1) << setw(w) << "show"      << "Shows an specific output: wave, report, coverage." << "\n";
    helpMessage << "For \"component\"" << "\n";
    helpMessage << doTabs(1) << setw(w) << "create"    << "Create a UVM component." << "\n";
    helpMessage << doTabs(1) << setw(w) << "edit"      << "Allow to edit each file of current UVMEnv project." << "\n";
    helpMessage << doTabs(1) << setw(w) << "delete"    << "Delete a UVM component." << "\n";
    helpMessage << doTabs(1) << setw(w) << "list"      << "List UVM components and RTL modules and signals." << "\n";

    print(helpMessage.str());
}


void createNewEnv(const string& projectName, const string& topModule){
    if(filesystem::exists(PROJECT_DIR + PATH_SEP + projectName)){
        printError("The UVMEnv project " + projectName + " already exists. Please choose another name.");
        return;
    }
    string formattedPName = toPascalCase(projectName);

    // Create directories structure
    filesystem::create_directory(PROJECT_DIR + PATH_SEP + formattedPName);
    filesystem::current_path(PROJECT_DIR + PATH_SEP + formattedPName);

    // Create UVMenv structure directories
    filesystem::create_directory("HDLSrc");
    filesystem::create_directory("OSimon");
    filesystem::create_directories("Itface" + PATH_SEP + "_impl");
    filesystem::copy(
        BASES_COMPONENT_DIR + PATH_SEP + "BFMBase.py",
        "Itface" + PATH_SEP + "BFM.py"
    );
    filesystem::create_directory("UVM_TB");

    // Create config file
    json configContent;
    configContent["id"] = base64_encode("uvm:" + formattedPName + ":env");
    configContent["name"] = formattedPName;
    configContent["simulation"] = {
        {"tool", "icarus"},
        {"time_unit_mag", 1},
        {"time_unit",     "ns"},
        {"time_prec_mag", 1},
        {"time_prec",     "ps"}
    };
    configContent["dut_design"] = {
        {"type", "combinatorial"},
        {"top_module", topModule}
    };
    configContent["dut_cs4seq"] = {
        {"clock_name",     "clk"},
        {"clock_edge_act", "high"},
        {"reset_name",     "rst"},
        {"reset_edge_act", "high"},
        {"sync_cycles", 1},
        {"clock_period", 1},
        {"cycles4wait_reset", 1}
    };
    configContent["uvm_components"] = {
        {"itface", {
            {"bfm_impl", "BfmDefault"}
        }},
        {"refmdl", {
            {"refmdl_impl", "RefDefault"}
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
    Top::instance().setProjectName(formattedPName);
    Top::instance().setTopModuleName(topModule);
    top -> copyBaseFile();
    
    filesystem::current_path(PROJECT_DIR);
}


void runCurrentProject(const string& waveLevel){
    // TODO: use wavelevel when writing waveform
    string rtlFiles = execCmdReturn(getScript("sys_commands") + "getRTLFullFiles " + DUT_HDL_DIR);
    string pyVersion = getPythonVersion();
    string vcdLevel = waveLevel == "" ? "1" : waveLevel;

    // Read JSON config file (config.json)
    ifstream f(CONFIG_FILE);
    json config = json::parse(f);

    // Extract necessary values
    string top_module = config["dut_design"].value("top_module", "unknown");
    string projName   = config.value("name", "unknown");

    string simtool        = config["simulation"].value("tool", "icarus");
    int time_unit_mag     = config["simulation"].value("time_unit_mag", 1);
    string time_unit      = config["simulation"].value("time_unit",     "ns");
    int time_prec_mag     = config["simulation"].value("time_prec_mag", 1);
    string time_prec      = config["simulation"].value("time_prec",     "ps");

    stringstream time_unit_stream, time_prec_stream;
    time_unit_stream << time_unit_mag << time_unit;
    time_prec_stream << time_prec_mag << time_prec;

    // Create/Override Makefile
    ofstream makefile("Makefile");

    if (makefile.is_open()) {
        makefile << "CWD = $(shell pwd)" << "\n";
        makefile << "SRC = " << rtlFiles << "\n";
        makefile << "TOPLEVEL_LANG ?= verilog\n";
        makefile << "\n\n";

        makefile << "SIM = " << simtool << "\n";
        makefile << "TOPLEVEL = " << top_module << "\n";
        makefile << "MODULE = Top" << projName << "\n";
        makefile << "\n\n";

        makefile << "COCOTB_HDL_TIMEUNIT = " << time_unit_stream.str() << "\n";
        makefile << "COCOTB_HDL_TIMEPRECISION = " << time_prec_stream.str() << "\n";
        makefile << "export WAVES = 1" << "\n";
        makefile << "\n\n";

        makefile << "ifeq ($(SIM),verilator)" << "\n";
        makefile << "    EXTRA_ARGS += --timescale " << time_unit_stream.str() << "/" << time_prec_stream.str() << " --trace -Wno-WIDTHEXPAND -Wno-fatal" << "\n";
        makefile << "    VERILOG_SOURCES = $(SRC)" << "\n";
        makefile << "else" << "\n";
        makefile << "    $(shell echo \"\\`timescale " << time_unit_stream.str() << "/" << time_prec_stream.str() << "\" > timescale.v)" << "\n";
        makefile << "    VERILOG_SOURCES = $(CWD)/timescale.v $(SRC)" << "\n";
        makefile << "endif" << "\n";
        makefile << "\n\n";

        makefile << "include $(shell cocotb-config --makefiles)/Makefile.sim" << "\n";
        makefile << "\n\n";

        makefile.close();
    } else {
        printError("Error: Impossible to create Makefile.");
    }


    // ==================================================================
    // Main running process
    // ==================================================================
    static py::scoped_interpreter guard{};

    py::module_ sys = py::module_::import("sys");
    sys.attr("path").attr("append")(DUT_HDL_DIR);

    filesystem::current_path(DUT_HDL_DIR);

    const string& rtlFullFiles = trim( execCmdReturn(getScript("sys_commands") + "getRTLFullFiles " + DUT_HDL_DIR) );
    string topFile = "";

    for(const string& s: splitString(rtlFullFiles, ' ')){
        // s.contains(topModule) // Since C++23
        if(s.find(top_module) != string::npos){
            topFile = s;
            break;
        }
    }
    
    filesystem::current_path(PROJECT_DIR);

    execCmdSimple(getScript("python_control") + "runUVMEnvProject " + PROJECT_DIR + " " + pyVersion);

    if(simtool == "icarus"){
        filesystem::rename(
            joinStr({"sim_build", top_module + ".fst"}, PATH_SEP),
            joinStr({OUTSIM_DIR, "dut_signals.vcd"}, PATH_SEP)
        );
    }
    else if(simtool == "verilator"){
        filesystem::rename(
            "dump.vcd",
            joinStr({OUTSIM_DIR, "dut_signals.vcd"}, PATH_SEP)
        );
    }
    else{
        printWarning("Simulation tool not recognized. No waveform file was generated.");
    }
    // ==================================================================


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
        print(name);
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
        
        // Copy the base file of signals getter into aux signals.py
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

// This function validates existing arguments not empty (does not work if arg is null)
// TODO: let be able to validate also null
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
        py::module_ readingPy = py::module_::import("signals");
        py::object resultado = readingPy.attr("get_signals")("obj_dir/V"+module+".h", writeOption, option);
        std::vector<Signal> signals = resultado.cast<std::vector<Signal>>();

        return signals;
    } catch (py::error_already_set &e) {
        stringstream err("[Error de Python] (signals) ");
        err << e.what() << "\n";
        printError(err.str());
        return {};
    }
}



