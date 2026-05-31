#ifndef PROJECT_OPT_HANDLER_H
#define PROJECT_OPT_HANDLER_H

#include <vector>
#include <string>

class ProjectCtxHandler {
    public:
    int cmdProject(const std::vector<std::string>& args);

    private:
    int runInit();
    int runView();
    int runRun();
    int runWave();
    int runReport();
};

#endif // PROJECT_OPT_HANDLER_H
