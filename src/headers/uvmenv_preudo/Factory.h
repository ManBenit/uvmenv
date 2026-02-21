#pragma once

#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <unordered_map>

using namespace std;

// Pseudoclasses for describing environment
class UVMObject {
protected:
    string name;

public:
    virtual void printInfo() = 0;
};

class UVMComponent {
protected:
    string parent;
    string name;
    
public:
    virtual void printInfo() = 0;
};


#endif // FACTORY_H


