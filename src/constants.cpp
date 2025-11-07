#include <filesystem>
#include "headers/constants.h"

bool IS_PY10_OR_MINOR = true;
float PY_VERSION = 3.10;

string getUser(){
    #ifdef _WIN32
        cout << "Windows (32/64 bit)" << endl;
        return getenv("USERNAME");
    #elif defined(_WIN64)
        cout << "Windows 64 bit" << endl;
        return getenv("USERNAME");
    #elif defined(__APPLE__) || defined(__MACH__)
        cout << "macOS" << endl;
        return getenv("USER");
    #elif defined(__linux__)
        return getenv("USER");
    #elif defined(__unix__)
        cout << "Unix" << endl;
        return getenv("USER");
    #elif defined(__posix__)
        cout << "Compatible POSIX" << endl;
        return getenv("USER");
    #else
        cout << "Unknown OS" << endl;
        return 3;
    #endif
}

//************** DIRECTORIES **************//
// Main paths
string getHomeDir(){
    return "/home/" + getUser() + "/Github/uvmenv";
}

string getVenvDir(){
    return "/home/" + getUser() + "/.UVMEnv_virtualenv";
}

string getToolsDir(){
    return getHomeDir() + "/uvmenv_tools";
}

string getBasesDir(){
    return getHomeDir() + "/uvmenv_bases";
}

string getBasesRepresentDir(){
    return getBasesDir() + "/representative_files";
}
string getBasesComponentDir(){
    return getBasesDir() + "/component_files";
}
string getBasesCommandDir(){
    return getBasesDir() + "/command_files";
}
string getBasesConfigDir(){
    return getBasesDir() + "/config_files";
}
string getProjectDir(){
    return filesystem::current_path().string();
}

// UVMEnv paths for writing base of representative files of UVM structure
// (Used when full verification construction will be done and when build the project)
string getDUTHdlDir(){
    return getProjectDir() + "/HDLSrc";
}
string getTbenchDir(){
    return getProjectDir() + "/UVM_TB";
}
string getOutsimDir(){
    return getProjectDir() + "/OSimon";
}
string getEnvironmentDir(){
    return getTbenchDir() + "/Envmnt";
}
string getBfmDir(){
    return getProjectDir() + "/Itface";
}

// UVM paths
string getScoreboardDir(){
    return getEnvironmentDir() + "/Scorbd";
}
string getRefmodelDir(){
    return getEnvironmentDir() + "/RefMdl";
}
string getAgentsDir(){
    return getEnvironmentDir() + "/Agents";
}
string getMiscelanousDir(){
    return getTbenchDir() + "/Misces";
}
string getSequencesDir(){
    return getTbenchDir() + "/Seqnce";
}
string getSeqitemsDir(){
    return getTbenchDir() + "/SeqItm";
}
string getRefmodelImplDir(){
    return getRefmodelDir() + "/_impl";
}
string getBfmImplDir(){
    return getBfmDir() + "/_impl";
}

//************** FILES ************** //
string getConfigFile(){
    return getProjectDir() + "/config.json";
}
string getUtilsFile(){
    return getProjectDir() + "/utils.py";
}
string getPathsFile(){
    return getProjectDir() + "/paths.py";
}
string getRunFile(){
    return getToolsDir() + "/run.sh";
}

// Representative files
string getEnvironmentFile(){
    return getEnvironmentDir() + "/Environment.py";
}
string getTestFile(){
    return getTbenchDir() + "/Test.py";
}
string getTopFilePrefix(){
    return getProjectDir() + "/Top_";
}

// *** BASES *** //
// Command files
string getPortGetterFilebase(){
    return getBasesCommandDir() + "/getPortsBase.py";
}
string getSignalGetterFilebase(){
    return getBasesCommandDir() + "/getSignalsBase.py";
}
string getVcdWrhelperFilebase(){
    return getBasesCommandDir() + "/writeVcdPart.py";
}

// Component files
string getAgentFilebase(){
    return getBasesComponentDir() + "/AgentBase.py";
}
string getAgentCovcolFilebase(){
    return getBasesComponentDir() + "/AgentCoverageCollectorBase.py";
}
string getAgentDriverFilebase(){
    return getBasesComponentDir() + "/AgentDriverBase.py";
}
string getAgentMonitorFilebase(){
    return getBasesComponentDir() + "/AgentMonitorBase.py";
}
string getBfmFilebase(){
    return getBasesComponentDir() + "/BFMBase.py";
}
string getBfmImplFilebase(){
    return getBasesComponentDir() + "/BFMImplBase.py";
}
string getRefmodelFilebase(){
    return getBasesComponentDir() + "/RefmodelBase.py";
}
string getRefmodelImplFilebase(){
    return getBasesComponentDir() + "/RefmodelImplBase.py";
}
string getScoreboardFilebase(){
    return getBasesComponentDir() + "/ScoreboardBase.py";
}
string getSeqitemFilebase(){
    return getBasesComponentDir() + "/SeqItemBase.py";
}
string getSeqitemRequestFilebase(){
    return getBasesComponentDir() + "/SeqItemRequestBase.py";
}
string getSeqitemResponseFilebase(){
    return getBasesComponentDir() + "/SeqItemResponseBase.py";
}
string getSequenceFilebase(){
    return getBasesComponentDir() + "/SequenceBase.py";
}

// Config files
string getPathsFilebase(){
    return getBasesConfigDir() + "/PathsFileBase.py";
}
string getUtilsFilebase(){
    return getBasesConfigDir() + "/UtilsFileBase.py";
}
string getReportFilebase(){
    return getBasesConfigDir() + "/UVMEnvReportBase.py";
}

// Representative files
string getEnvironmentFilebase(){
    return getBasesRepresentDir() + "/EnvironmentBase.py";
}
string getTestFilebase(){
    return getBasesRepresentDir() + "/TestBase.py";
}
string getTopFilebase(){
    return getBasesRepresentDir() + "/TopBase.py";
}


