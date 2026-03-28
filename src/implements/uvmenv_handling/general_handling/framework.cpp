#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../../../headers/uvmenv_preudo/components/Top.h"
#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
using namespace std;
using json = nlohmann::json;



bool isUVMEnvProject(const string& path){
    vector<string> pdirParts = splitString( path, PATH_SEP.at(0) );
    string projectIdExpected = "uvm:" + pdirParts[pdirParts.size()-1] + ":env";
    string configFileName = path + PATH_SEP + "config.json";

    
    if( !filesystem::exists(configFileName) ){
        return false;
    }

    ifstream config_file(configFileName);
    json configFileData = json::parse(config_file);
    
    return base64_decode( configFileData["id"] ) == projectIdExpected;
} 


bool existsDUT(){
    string rtlFiles = execCmdReturn(getScript("sys_commands") + "validateRTLExistence " + DUT_HDL_DIR);
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
    // Create directories structure
    filesystem::create_directory(PROJECT_DIR + PATH_SEP + projectName);
    filesystem::current_path(PROJECT_DIR + PATH_SEP + projectName);

    // Create UVMenv structure directories
    filesystem::create_directory("HDLSrc");
    filesystem::create_directory("OSimon");
    filesystem::create_directories("Itface" + PATH_SEP + "_impl");
    filesystem::create_directories("UVM_TB" + PATH_SEP + "SeqItm");
    filesystem::create_directories("UVM_TB" + PATH_SEP + "Seqnce");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt");
    filesystem::create_directories("UVM_TB" + PATH_SEP + "Misces");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "Scorbd");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "Agents");
    //filesystem::create_directories("UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "RefMdl" + PATH_SEP + "_impl");

    // Create config file
    ofstream config_file("config.json");
    config_file << "{\n";
    config_file << TAB << "\"id\": \"" << base64_encode("uvm:"+projectName+":env") << "\",\n";
    config_file << TAB << "\"name\": \"" << projectName << "\",\n";
    config_file << TAB << "\"simtool\": \"icarus\",\n";
    config_file << TAB << "\"dut_design\": {\n";
    config_file << TAB << TAB << "\"type\": \"combinatorial\",\n";
    config_file << TAB << TAB << "\"top_module\": \"" << topModule << "\",\n";
    config_file << TAB << TAB << "\"sync_clock_cycles\": \"1\"\n";
    config_file << TAB << "},\n";
    // config_file << TAB << "\"top_extension\""
    config_file << TAB << "\"uvm_components\": {\n";
    config_file << TAB << TAB << "\"itface\": {\n";
    config_file << TAB << TAB << TAB << "\"bfm_impl\": \"DefaultBfmImpl\"\n";
    config_file << TAB << TAB << "},\n";
    config_file << TAB << TAB << "\"refmdl\": {\n";
    config_file << TAB << TAB << TAB << "\"refmdl_impl\": \"DefaultRefModelImpl\"\n";
    config_file << TAB << TAB << "}\n";
    config_file << TAB << "}\n";
    config_file << "}\n";
    config_file.close();

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
    filesystem::copy(BFM_FILEBASE, "Itface" + PATH_SEP + "BFM.py");

    ////// Write interface for Reference model
    //filesystem::copy(REFMODEL_FILEBASE, "UVM_TB" + PATH_SEP + "Envmnt" + PATH_SEP + "RefMdl/RefModel.py");

    ////// Write report mechanism
    filesystem::copy(REPORT_FILEBASE, "UVM_TB" + PATH_SEP + "Misces" + PATH_SEP + "UVMEnvReport.py");

    filesystem::current_path(PROJECT_DIR);
}


void runCurrentProject(){
    string rtlFiles = execCmdReturn(getScript("sys_commands") + "getRTLfiles " + DUT_HDL_DIR);
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





