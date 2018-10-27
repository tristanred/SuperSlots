#pragma once

#include "SuperSlotsSupport.h"

class SuperSlotsSupport_CLASS Symbol
{
public:
    Symbol();
    Symbol(int id);
    ~Symbol();

    int id;
    char* name; // Optional
    bool isWild;
    bool isScatter;
};

class SuperSlotsSupport_CLASS SymbolSet
{
public:
    SymbolSet();
    ~SymbolSet();

    int SymbolCount;
    Symbol** SymbolList;

    static SymbolSet* CreateFromConfig(const char* configPath);
    static SymbolSet* CreateDefaultSet();
};