#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <filesystem>
using namespace std;

//************** COLORS **************//
#define C_RED     "\033[31m"
#define C_BLUE    "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN    "\033[36m"
#define C_GREEN   "\033[32m"
#define C_YELLOW  "\033[33m"
#define C_WHITE   "\033[37m"
#define C_N       "\033[0m"   // reset
////////////////////////////////////////

#define TAB "    "  // 4 spaces to make a tab into Python generated files


//************** USER **************//
string getUser();

//************** DIRECTORIES **************//
// Main paths
string getHomeDir();
string getVenvDir();
string getToolsDir();
string getBasesDir();
string getBasesRepresentDir();
string getBasesComponentDir();
string getBasesCommandDir();
string getBasesConfigDir();
string getProjectDir();

// UVMEnv directories
string getDUTHdlDir();
string getTbenchDir();
string getOutsimDir();
string getEnvironmentDir();
string getBfmDir();

// UVM subdirectories
string getScoreboardDir();
string getRefmodelDir();
string getAgentsDir();
string getMiscelanousDir();
string getSequencesDir();
string getSeqitemsDir();
string getRefmodelImplDir();
string getBfmImplDir();

//************** FILES **************//
string getConfigFile();
string getUtilsFile();
string getPathsFile();
string getRunFile();

// Representative files
string getEnvironmentFile();
string getTestFile();
string getTopFilePrefix();

//************** BASES **************//
// Command files
string getPortGetterFilebase();
string getSignalGetterFilebase();
string getVcdWrhelperFilebase();

// Component files
string getAgentFilebase();
string getAgentCovcolFilebase();
string getAgentDriverFilebase();
string getAgentMonitorFilebase();
string getBfmFilebase();
string getBfmImplFilebase();
string getRefmodelFilebase();
string getRefmodelImplFilebase();
string getScoreboardFilebase();
string getSeqitemFilebase();
string getSeqitemRequestFilebase();
string getSeqitemResponseFilebase();
string getSequenceFilebase();

// Config files
string getPathsFilebase();
string getUtilsFilebase();
string getReportFilebase();

// Representative files
string getEnvironmentFilebase();
string getTestFilebase();
string getTopFilebase();

#endif // CONSTANTS_H

