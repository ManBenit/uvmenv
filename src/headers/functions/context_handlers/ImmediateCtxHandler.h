#ifndef IMMEDIATE_OPT_HANDLER
#define IMMEDIATE_OPT_HANDLER

#include <string>
#include <vector>

class ImmediateCtxHandler {
    public:
    int cmdNew(const std::vector<std::string>& args);
    int cmdSearch();
    int cmdHelp();
};

#endif // IMMEDIATE_OPT_HANDLER