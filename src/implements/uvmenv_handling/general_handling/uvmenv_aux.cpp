#include <string>
#include <stdexcept>
#include <array>

#include "../../../headers/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../headers/functions/utils.h"
#include "../../../headers/functions/constants.h"
using namespace std;


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


string getScript(const string& name){
    return INSTALL_DIR + SCRIPTS_DIR + PATH_SEP + name + SCRIPTS_EXT + " ";
}


string getPythonVersion(){
    string python_version_cmd = "python3 --version | awk '{print $2}' | cut -d'.' -f1,2";
    return execCmdReturn(python_version_cmd);
}

void activatePythonVenv(){
    float version = stof(getPythonVersion());
    if(version >= 3.10){
        string activate_cmd = "bash -c 'source " + VENV_DIR + "/bin/activate'";
        execCmdSimple(activate_cmd);
    }
}

