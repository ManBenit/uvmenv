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
    helpMessage << "Usage:\t uvmenv <ctx> <opt> <comp> <name> [<other>] [--options]" << "\n\n";

    helpMessage << "COMMAND is mandatory." << "\n";
    helpMessage << "OPTION is required by COMMAND \"project\" and \"component\"." << "\n";
    helpMessage << "COMPONENT is required when COMMAND is \"component\"." << "\n";
    helpMessage << "PARAMETERS are required depending on the OPTION and COMPONENT." << "\n";

    helpMessage << "\n";

    helpMessage << "COMMAND" << "\n";
    helpMessage << left; // Alineación a la izquierda para el comando
    helpMessage << doTabs(1) << setw(w) << "new"       << "Create a new UVMEnv project." << "\n";
    helpMessage << doTabs(1) << setw(w) << "search"    << "Look for UVMEnv projects into current directory." << "\n";
    helpMessage << doTabs(1) << setw(w) << "help"      << "Show this help." << "\n";
    helpMessage << doTabs(1) << setw(w) << "project"   << "Manage current project." << "\n";
    helpMessage << doTabs(1) << setw(w) << "component" << "Manage UVM components of current project." << "\n";

    helpMessage << "\n";

    helpMessage << "OPTION" << "\n";
    helpMessage << "For \"project\"" << "\n";
    helpMessage << doTabs(1) << setw(w) << "init"      << "Create default structure with only one test and environment." << "\n";
    helpMessage << doTabs(1) << setw(w) << "view"      << "Shows project tree." << "\n";
    helpMessage << doTabs(1) << setw(w) << "run"       << "Starts verification process." << "\n";
    helpMessage << doTabs(1) << setw(w) << "wave"      << "Shows waveform." << "\n";
    helpMessage << doTabs(1) << setw(w) << "report"    << "Shows the report file content." << "\n";
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
    configContent["simtool"] = "icarus";
    configContent["dut_design"] = {
        {"type", "combinatorial"},
        {"top_module", topModule},
        {"sim_units", "ns"}
    };
    configContent["dut_cs4seq"] = {
        {"clock_name", "clk"},
        {"reset_name", "rst"},
        {"sync_cycles", 1},
        {"clock_period", 1},
        {"cycles4wait_reset", 1}
    };
    configContent["uvm_components"] = {
        {"itface", {
            {"bfm_impl", "BFMDefault"}
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

    // Leer el archivo de configuración JSON
    ifstream f(CONFIG_FILE);
    json config = json::parse(f);

    // Extraer valores del JSON (equivalente a jq)
    string simtool = config.value("simtool", "icarus");
    string top_module = config["dut_design"].value("top_module", "unknown");
    string projName = config.value("name", "unknown");

    // Crear/Sobrescribir el archivo Makefile
    ofstream makefile("Makefile");

    if (makefile.is_open()) {
        makefile << "CWD = $(shell pwd)\n";
        makefile << "HDL_SRC = " << simtool << "\n";
        makefile << "SIM ?= " << simtool << "\n";
        makefile << "\n\n";
        
        makefile << "VERILOG_SOURCES = " << rtlFiles << "\n";
        makefile << "\n\n";
        
        makefile << "MODULE = Top" << projName << "\n";
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
        printError("Error: Impossible to create Makefile.");
    }


    // ==================================================================
    // Main running process
    // ==================================================================
    static py::scoped_interpreter guard{};

    py::module_ sys = py::module_::import("sys");
    sys.attr("path").attr("append")(DUT_HDL_DIR);

    filesystem::current_path(DUT_HDL_DIR);
    
    // Get necessary data for VCD writer
    string topModule = config["dut_design"]["top_module"];

    const string& rtlFullFiles = trim( execCmdReturn(getScript("sys_commands") + "getRTLFullFiles " + DUT_HDL_DIR) );
    string topFile = "";

    for(const string& s: splitString(rtlFullFiles, ' ')){
        // s.contains(topModule) // Since C++23
        if(s.find(topModule) != string::npos){
            topFile = s;
            break;
        }
    }

    // Copy VCD writer file
    if( !filesystem::exists("vcdWriter.py") )
        filesystem::copy(VCD_WRHELPER_FILEBASE, "vcdWriter.py");
        
    // Run VCD writer (delete endmodule and write VCD dump)
    //// TODO: parametrize VCD level to get it from user option (instead of 4)
    runVcdWriter(topFile, "4", "1");
    runVcdWriter(topFile, "4", "2");
    
    filesystem::current_path(PROJECT_DIR);



    execCmdSimple(getScript("python_control") + "runUVMEnvProject " + PROJECT_DIR + " " + pyVersion);


    // Run VCD writer (delete written code and rewrite endmodule)
    filesystem::current_path(DUT_HDL_DIR);
    runVcdWriter(topFile, "4", "3");
    
    // Remove VCD writer
    filesystem::remove("vcdWriter.py");

    filesystem::current_path(PROJECT_DIR);

    filesystem::rename("dut_signals.vcd", joinStr({OUTSIM_DIR, "dut_signals.vcd"}, PATH_SEP));
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


void runVcdWriter(const string& topFile, const string& vcdLevel, const string& runningMode){
    try{
        py::module_ readingPy = py::module_::import("vcdWriter");
        readingPy.attr("write_vcd")(topFile, vcdLevel, runningMode);
    } catch (py::error_already_set &e) {
        stringstream err("[Error de Python (vcd)] ");
        err << e.what() << "\n";
        printError(err.str());
    }

}



