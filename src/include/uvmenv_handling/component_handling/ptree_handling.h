#include <string>
#include <vector>


// ==================
// BFM INTERFACE
// ==================
void treeAddInterface(const std::string& name);
std::vector<std::string> treeListInterface();
void treeDeleteInterface(const std::string& name);

// ==================
// TEST
// ==================
void treeAddTest(const std::string& name);
std::vector<std::string> treeListTest();
void treeDeleteTest(const std::string& name);

// ==================
// SEQUENCE ITEM
// ==================
void treeAddSeqitem(const std::string& name, const std::string& testName);
std::vector<std::string> treeListSeqitem(const std::string& testName);
void treeDeleteSeqitem(const std::string& name, const std::string& testName);

// ==================
// SEQUENCES
// ==================
void treeAddSequences(const std::string& name, const std::string& testName);
std::vector<std::string> treeListSequences(const std::string& testName);
void treeDeleteSequences(const std::string& name, const std::string& testName);

// ==================
// ENVIRONMENT
// ==================
void treeAddEnvironment(const std::string& name, const std::string& testName);
std::vector<std::string> treeListEnvironments(const std::string& testName);
void treeDeleteEnvironment(const std::string& name, const std::string& testName);

// ==================
// REFMODEL
// ==================
void treeAddRefmodel(const std::string& name, const std::string& testName, const std::string& envName);
std::vector<std::string> treeListRefmodel(const std::string& testName, const std::string& envName);
void treeDeleteRefmodel(const std::string& name, const std::string& testName, const std::string& envName);

// ==================
// AGENTS
// ==================
void treeAddAgent(const std::string& name, const std::string& testName, const std::string& envName);
std::vector<std::string> treeListAgents(const std::string& testName, const std::string& envName);
void treeDeleteAgent(const std::string& name, const std::string& testName, const std::string& envName);

// ==================
// SCOREBOARD
// ==================
void treeAddScoreboard(const std::string& name, const std::string& testName, const std::string& envName);
std::vector<std::string> treeListScoreboards(const std::string& testName, const std::string& envName);
void treeDeleteScoreboard(const std::string& name, const std::string& testName, const std::string& envName);
