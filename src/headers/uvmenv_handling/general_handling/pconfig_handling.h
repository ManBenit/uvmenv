#include <string>

std::string getProjectId(const std::string& currProj);
std::string getProjectName(const std::string& currProj);
std::string getProjectSimulation(const std::string& currProj, std::string field);
std::string getProjectDutDesign(const std::string& currProj, std::string field);
std::string getProjectDutCs4Seq(const std::string& currProj, std::string field);
std::string getProjectUvmComponents(const std::string& currProj, std::string field);

