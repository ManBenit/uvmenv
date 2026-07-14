#ifndef COMPONENT_OPT_HANDLER_H
#define COMPONENT_OPT_HANDLER_H

#include <vector>
#include <string>

class ComponentCtxHandler {
    public:
    int cmdComponent(const std::vector<std::string>& args, const std::string& test, const std::string& env, const std::string& module, const std::string& type);

    private:
    int runCreate(const std::vector<std::string>& args, const std::string& test, const std::string& env, const std::string& module, const std::string& type);
    int runList(const std::vector<std::string>& args, const std::string& test, const std::string& env);
    int runDelete(const std::vector<std::string>& args);
    int runEdit(const std::vector<std::string>& args, const std::string& test, const std::string& env);
    
};

#endif // COMPONENT_OPT_HANDLER_H
