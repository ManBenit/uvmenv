#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <cstdlib>
#include <filesystem>
using namespace std;

// =============================================
// Colors
// =============================================
#define C_RED     "\033[31m"
#define C_BLUE    "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN    "\033[36m"
#define C_GREEN   "\033[32m"
#define C_YELLOW  "\033[33m"
#define C_WHITE   "\033[37m"
#define C_N       "\033[0m"   // reset
// =============================================



#define TAB "    "  // 4 spaces to make a tab into Python generated files



// =============================================
// OS constants
// =============================================
#if defined(_WIN32) || defined(_WIN64)
    const string OS_NAME = "Windows";
    const string USER_VAR = getenv("USERNAME");
    const string PATH_SEP = "\\";
    const string SCRIPTS_DIR = "\\scripts\\batch";
    const string SCRIPTS_EXT = ".bat";
    const string HOME_DIR = getenv("UVMENV_HOME");
    const string INSTALL_DIR = HOME_DIR + "\\.UVMEnv";
    const string VENV_DIR = HOME_DIR + "\\.UVMEnv_virtualenv";
#elif defined(__APPLE__) || defined(__MACH__)
    const string OS_NAME = "MacOS";
    const string USER_VAR = getenv("USER");
    const string PATH_SEP = "/";
    const string SCRIPTS_DIR = "/scripts/bash";
    const string SCRIPTS_EXT = ".sh";
    const string HOME_DIR = getenv("UVMENV_HOME");
    const string INSTALL_DIR = HOME_DIR + "/.UVMEnv";
    const string VENV_DIR = HOME_DIR + "/.UVMEnv_virtualenv";
#elif defined(__linux__)
    const string OS_NAME = "Linux";
    const string USER_VAR = getenv("USER");
    const string PATH_SEP = "/";
    const string SCRIPTS_DIR = "/scripts/bash";
    const string SCRIPTS_EXT = ".sh";
    const string HOME_DIR = getenv("UVMENV_HOME");
    const string INSTALL_DIR = HOME_DIR + "/.UVMEnv";
    const string VENV_DIR = HOME_DIR + "/.UVMEnv_virtualenv";
#elif defined(__unix__)
    const string OS_NAME = "Unix";
    const string USER_VAR = getenv("USER");
    const string PATH_SEP = "/";
    const string SCRIPTS_DIR = "/scripts/bash";
    const string SCRIPTS_EXT = ".sh";
    const string HOME_DIR = getenv("UVMENV_HOME");
    const string INSTALL_DIR = HOME_DIR + "/.UVMEnv";
    const string VENV_DIR = HOME_DIR + "/.UVMEnv_virtualenv";
#elif defined(__posix__)
    const string OS_NAME = "Posix";
    const string USER_VAR = getenv("USER");
    const string PATH_SEP = "/";
    const string SCRIPTS_DIR = "/scripts/bash";
    const string SCRIPTS_EXT = ".sh";
    const string HOME_DIR = getenv("UVMENV_HOME");
    const string INSTALL_DIR = HOME_DIR + "/.UVMEnv";
    const string VENV_DIR = HOME_DIR + "/.UVMEnv_virtualenv";
#else
    const string OS_NAME = "Unknown";
#endif
// =============================================


// TODO: Finish to clear unused constants
//************** DIRECTORIES **************//
// const string HOME_DIR                  = "/home/" + USER_VAR + "/Github/uvmenv/install"; // Delete after dev
// const string INSTALL_DIR               = HOME_DIR; // Modify to HOME_DIR + PATH_SEP + ".UVMEnv";
// const string VENV_DIR                  = "/home/" + USER_VAR + "/.UVMEnv_virtualenv";// Modify to HOME_DIR + PATH_SEP + ".UVMEnv_virtualenv";

// Repository
const string TOOLS_DIR                 = INSTALL_DIR + PATH_SEP + "tools";
const string BASES_DIR                 = INSTALL_DIR + PATH_SEP + "bases";
const string BASES_REPRESENT_DIR       = BASES_DIR + PATH_SEP + "representative_files";
const string BASES_COMPONENT_DIR       = BASES_DIR + PATH_SEP + "component_files";
const string BASES_COMMAND_DIR         = BASES_DIR + PATH_SEP + "command_files";
const string BASES_CONFIG_DIR          = BASES_DIR + PATH_SEP + "config_files";  


const string PROJECT_DIR               = filesystem::current_path().string();
const string PYMODULE                  = "__init__.py";




// UVMEnv paths for writing base of representative files of UVM structure
// (Used when full verification construction will be done and when build the project)
const string DUT_HDL_DIR               = PROJECT_DIR + PATH_SEP + "HDLSrc";
const string TBENCH_DIR                = PROJECT_DIR + PATH_SEP + "UVM_TB";
const string OUTSIM_DIR                = PROJECT_DIR + PATH_SEP + "OSimon";

const string ENVIRONMENT_DIR           = TBENCH_DIR + PATH_SEP + "Envmnt";
const string BFM_DIR                   = PROJECT_DIR + PATH_SEP + "Itface";

// UVM paths
const string REFMODEL_DIR              = ENVIRONMENT_DIR + PATH_SEP + "RefMdl";
const string MISCELANEOUS_DIR          = TBENCH_DIR + PATH_SEP + "Misces";


//************** FILES ************** //
const string CONFIG_FILE               = PROJECT_DIR + PATH_SEP + "config.json";
const string UTILS_FILE                = PROJECT_DIR + PATH_SEP + "utils.py";
const string PATHS_FILE                = PROJECT_DIR + PATH_SEP + "paths.py";
const string RUN_FILE                  = TOOLS_DIR + PATH_SEP + "run.sh";

// Representative files
const string ENVIRONMENT_FILE          = ENVIRONMENT_DIR + PATH_SEP + "Environment.py";
const string TEST_FILE                 = TBENCH_DIR + PATH_SEP + "Test.py";
const string TOP_FILE_PREFIX           = PROJECT_DIR + PATH_SEP + "Top_";

// *** BASES *** //
// Command files
const string PORT_GETTER_FILEBASE      = BASES_COMMAND_DIR + PATH_SEP + " getPortsBase.py";
const string SIGNAL_GETTER_FILEBASE    = BASES_COMMAND_DIR + PATH_SEP + "getSignalsBase.py";
const string VCD_WRHELPER_FILEBASE     = BASES_COMMAND_DIR + PATH_SEP + "writeVcdPart.py";

// Component files
const string BFM_FILEBASE              = BASES_COMPONENT_DIR + PATH_SEP + "BFMBase.py";
const string REFMODEL_FILEBASE         = BASES_COMPONENT_DIR + PATH_SEP + "RefmodelBase.py";
const string SEQITEM_REQUEST_FILEBASE  = BASES_COMPONENT_DIR + PATH_SEP + "SeqItemRequestBase.py";
const string SEQITEM_RESPONSE_FILEBASE = BASES_COMPONENT_DIR + PATH_SEP + "SeqItemResponseBase.py";

// Config files
const string PATHS_FILEBASE            = BASES_CONFIG_DIR + PATH_SEP + "PathsFileBase.py";
const string UTIL_FILEBASE             = BASES_CONFIG_DIR + PATH_SEP + "UtilsFileBase.py";
const string REPORT_FILEBASE           = BASES_CONFIG_DIR + PATH_SEP + "UVMEnvReportBase.py";
const string SIGREADER_FILEBASE        = BASES_CONFIG_DIR + PATH_SEP + "SignalsReaderBase.py";


#endif // CONSTANTS_H

