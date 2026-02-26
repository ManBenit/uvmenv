#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../../../headers/uvmenv_handling/general_handling/framework.h"
#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
using namespace std;
using json = nlohmann::json;



bool isUVMEnvProject(const string& path){
    vector<string> pdirParts = splitString( path, '/' );
    string projectIdExpected = "uvm:" + pdirParts[pdirParts.size()-1] + ":env";
    string configFileName = path + PATH_SEP + "config.json";

    
    if( !filesystem::exists(configFileName) ){
        return false;
    }

    ifstream config_file(configFileName);
    json configFileData = json::parse(config_file);
    
    return base64_decode( configFileData["id"] ) == projectIdExpected;
} 


void showHelp() {
    cout << "Usage:\t uvmenv " << C_CYAN << "<OPTION>" << C_N << "\n" << endl;

    cout << "  OPTION:" << endl;
    cout << "\t" << C_MAGENTA << "Framework management" << C_N << endl;
    printOption("-n|--new", "Creates a new UVMEnv project.");
    printOption("-s|--search", "Looks for a valid UVMEnv project into current directory.");
    printOption("-h|--help", string("Shows ") + C_YELLOW + "uvmenv" + C_N + " command help into system browser (less).");
    printOption("-i|--init", "Create default templates for top module.\n\tBFM, reference model, sequence item, sequence, agent, scoreboard.");
    printOption("-v|--view", "Shows project tree into system browser (less).");
    printOption("run", "Starts verification process.");
    printOption("wave", "Shows wave form using GTKWave.");
    printOption("report", "Shows the report file content.");

    cout << "\t" << C_MAGENTA << "UVM Component handling" << C_N << endl;
    printOption("-c|--create", "Create a UVM component.");
    printOption("-l|--list", "List UVM components and RTL modules and signals.");
    printOption("-e|--edit", "Allow to edit each file of current UVMEnv project.");
    printOption("-d|--delete", "Delete a UVM component");

    cout << endl;
}


void createNewEnv(string projectName, string topModule){    
    // Create directories structure
    filesystem::create_directory(PROJECT_DIR + "/" + projectName);
    filesystem::current_path(PROJECT_DIR + "/" + projectName);

    // Create UVMenv structure directories
    filesystem::create_directory("HDLSrc"); // DUT_HDL_DIR
    filesystem::create_directory("OSimon"); // OUTSIM_DIR
    filesystem::create_directories("Itface/_impl");
    filesystem::create_directories("UVM_TB/SeqItm");
    filesystem::create_directories("UVM_TB/Seqnce");
    filesystem::create_directories("UVM_TB/Envmnt");
    filesystem::create_directories("UVM_TB/Misces");
    filesystem::create_directories("UVM_TB/Envmnt/Scorbd");
    filesystem::create_directories("UVM_TB/Envmnt/Agents");
    filesystem::create_directories("UVM_TB/Envmnt/RefMdl/_impl");

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
    //filesystem::copy(TOP_FILEBASE, "Top_"+topModule+".py");

    ////// Write Test
    //filesystem::copy(TEST_FILEBASE, "UVM_TB/Test.py");

    ////// Write Environment
    //filesystem::copy(ENVIRONMENT_FILEBASE, "UVM_TB/Envmnt/Environment.py");

    ////// Write interface for BFM
    filesystem::copy(BFM_FILEBASE, "Itface/BFM.py");

    ////// Write interface for Reference model
    filesystem::copy(REFMODEL_FILEBASE, "UVM_TB/Envmnt/RefMdl/RefModel.py");

    ////// Write report mechanism
    filesystem::copy(REPORT_FILEBASE, "UVM_TB/Misces/UVMEnvReport.py");

    filesystem::current_path(PROJECT_DIR);
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





