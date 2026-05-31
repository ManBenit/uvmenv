#ifndef PROJECT_OPT_HANDLER_H
#define PROJECT_OPT_HANDLER_H

class ProjectOptHandler {
    public:
    int cmdProject();

    private:
    int runCreate();
    int runList();
    int runDelete();
    int runEdit();
};

#endif // PROJECT_OPT_HANDLER_H
