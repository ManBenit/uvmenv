// ******************************************************* //
//                 ENVIRONMENT HANDLING                    //
// ******************************************************* //

#include "../../headers/functions/env_handling.h"

void createNewEnv(string projectName, string topModule){    
    // Create directories structure
    filesystem::create_directory(getProjectDir() + "/" + projectName);
    filesystem::current_path(getProjectDir() + "/" + projectName);

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
    filesystem::copy(getUtilsFilebase(), "utils.py");

    ////// Write script of paths
    filesystem::copy(getPathsFilebase(), "paths.py");

    ////// Write Top
    filesystem::copy(getTopFilebase(), "Top_"+topModule+".py");

    ////// Write Test
    filesystem::copy(getTestFilebase(), "UVM_TB/Test.py");

    ////// Write Environment
    filesystem::copy(getEnvironmentFilebase(), "UVM_TB/Envmnt/Environment.py");

    ////// Write interface for BFM
    filesystem::copy(getBfmFilebase(), "Itface/BFM.py");

    ////// Write interface for Reference model
    filesystem::copy(getRefmodelFilebase(), "UVM_TB/Envmnt/RefMdl/RefModel.py");

    ////// Write report mechanism
    filesystem::copy(getReportFilebase(), "UVM_TB/Misces/UVMEnvReport.py");

    filesystem::current_path(getProjectDir());
}

void searchProjects(){
    vector<string> projects;
    if(isUVMEnvProject())
        printInfo("You are currently into a UVMEnv project");
    else
        for (const auto& entry : filesystem::directory_iterator(getProjectDir())) {
            if (filesystem::is_directory(entry.status())) {
                filesystem::current_path(entry.path());
                if(isUVMEnvProject()) projects.push_back(entry.path().filename());
                filesystem::current_path(getProjectDir());
            } 
        }

    for(const auto& name: projects)
        cout << name << endl;
}

void showModules(){
    ////local modules_dir=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sort | uniq))
    //local modules_dir=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq))
    ////readarray -t modules_dir <<< "$(ls -F $DUT_HDL_DIR | grep -v "/" | grep -E "sv|v")"

    /*for archivo in "${modules_dir[@]}"; do
        nom=$(echo $archivo | cut -d'.' -f1)
        if [ "$nom" == "$(jq -r '.dut_design.top_module' $CONFIG_FILE)" ]; then
            echo -e "${C_CYAN}$nom [Top]${C_N}"
        else
            echo "$nom"
        fi
    done*/
}
