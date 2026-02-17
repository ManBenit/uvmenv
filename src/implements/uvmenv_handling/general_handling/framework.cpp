#include "../../../headers/uvmenv_handling/general_handling/framework.h"

void execCmdSimple(const string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "w");
    if (!pipe) {
        throw runtime_error("[CMD simple] popen() failed");
    }
    pclose(pipe);
}

string execCmdReturn(const string& cmd){
    array<char, 128> buffer{};
    string result;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw runtime_error("[CMD return] popen() failed");
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);

    //cout << result << endl;

    return result;
}

bool isUVMEnvProject(){
    vector<string> pdirParts = splitString( getProjectDir(), '/' );
    string projectIdExpected = "uvm:" + pdirParts[pdirParts.size()-1] + ":env";
    string configFileName = "config.json";

    
    if( !filesystem::exists(configFileName) )
        return false;

    ifstream config_file(configFileName);
    json configFileData = json::parse(config_file);
    if( base64_decode(configFileData["id"]) != projectIdExpected )
        return false;

    return true;
} 

string getScript(const string& name){
    return getScriptsPath() + "/" + name + getScriptsExtension() + " ";
}


string getPythonVersion(){
    string python_version_cmd = "python3 --version | awk '{print $2}' | cut -d'.' -f1,2";
    return execCmdReturn(python_version_cmd);
}

void activatePythonVenv(){
    float version = stof(getPythonVersion());
    if(version >= 3.10){
        string activate_cmd = "bash -c 'source " + getVenvDir() + "/bin/activate'";
        execCmdSimple(activate_cmd);
    }
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