#ifndef UVMENV_AUX
#define UVMENV_AUX

#include <string>



void execCmdSimple(const std::string& cmd);
std::string execCmdReturn(const std::string& cmd);


std::string getScript(const std::string& name);

std::string getPythonVersion();


#endif // UVMENV_AUX


