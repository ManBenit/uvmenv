#ifndef TOP_H
#define TOP_H

#include "../UVMComponent.h"

class Top: public UVMComponent {

public:
    static Top& instance();

    // Nobody must create other
    Top(const Top&) = delete;
    Top& operator=(const Top&) = delete;

    void copyBaseFile() override;

private:
    Top();
    static Top* m_instance;

};

#endif // TOP_H