#include <string>
#include <stdexcept>
#include <array>
#include <iostream>

#include "../../../include/uvmenv_handling/general_handling/uvmenv_aux.h"
#include "../../../include/functions/utils.h"
#include "../../../include/functions/constants.h"
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

// Possible to omit this function, but tests are pending to validate this proposal
string getPythonVersion(){
    string pyVersionNumber = splitString(execCmdReturn("python3 --version"), ' ')[1];
    string pyVersionMajor = splitString(pyVersionNumber, '.')[0];
    string pyVersionMinor = splitString(pyVersionNumber, '.')[1];
    return pyVersionMajor + "." + pyVersionMinor;
}

