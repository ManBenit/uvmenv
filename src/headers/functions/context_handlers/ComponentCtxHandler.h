#ifndef COMPONENT_OPT_HANDLER_H
#define COMPONENT_OPT_HANDLER_H

class ComponentOptHandler {
    public:
    int cmdComponent();

    private:
    int runInit();
    int runView();
    int runRun();
    int runWave();
    int runReport();
};

#endif // COMPONENT_OPT_HANDLER_H
