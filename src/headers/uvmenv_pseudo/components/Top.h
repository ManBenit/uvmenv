#ifndef TOP_H
#define TOP_H

#include <string>
#include "../UVMComponent.h"

class Top: public UVMComponent {

public:
    static Top& instance();

    // Nobody must create other
    Top(const Top&) = delete;
    Top& operator=(const Top&) = delete;

    void copyBaseFile() override;

    void editFile(const std::string& name);

    void setTopModuleName(const std::string& topModuleName);
    void setProjectName(const std::string& projectName);

private:
    Top();
    static Top* m_instance;
    std::string topModuleName;
    std::string projectName;

};

#endif // TOP_H