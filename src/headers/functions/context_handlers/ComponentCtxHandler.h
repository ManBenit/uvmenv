#ifndef COMPONENT_OPT_HANDLER_H
#define COMPONENT_OPT_HANDLER_H

#include <vector>
#include <string>

class ComponentCtxHandler {
    public:
    int cmdComponent(const std::vector<std::string>& args);

    private:
    int runCreate(const std::vector<std::string>& args);
    int runList(const std::vector<std::string>& args);
    int runDelete(const std::vector<std::string>& args);
    int runEdit(const std::vector<std::string>& args);
    
};

#endif // COMPONENT_OPT_HANDLER_H
