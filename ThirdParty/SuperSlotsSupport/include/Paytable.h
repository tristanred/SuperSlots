#pragma once

#include "SuperSlotsSupport.h"

class Symbol;
class SymbolSet;

class SuperSlotsSupport_CLASS PaytablePrize
{
public:
    PaytablePrize();
    ~PaytablePrize();

    int SymbolID;
    int SymbolCount;
    int PrizeWins;
};

class SuperSlotsSupport_CLASS Paytable
{
public:
    Paytable();
    ~Paytable();

    static Paytable* GetPaytableFromConfig(const char* configPath, SymbolSet* symbols);
    static Paytable* GetDefaultPaytable(SymbolSet* symbols);

    int PrizeCount;
    PaytablePrize** Prizes;
};