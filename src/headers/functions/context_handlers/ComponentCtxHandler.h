#ifndef COMPONENT_OPT_HANDLER_H
#define COMPONENT_OPT_HANDLER_H

class ComponentCtxHandler {
    public:
    int cmdComponent();

    private:
    int runCreate();
    int runList();
    int runDelete();
    int runEdit();
    
};

#endif // COMPONENT_OPT_HANDLER_H
