#pragma once 
#include "PskPrinter.h"
#include "TscPrinter.h"
#include "ZbraPrinter.h"
#define DLL_EXPORT __declspec(dllexport) 
extern "C" DLL_EXPORT bool	 Print2(char* pp,int type);
extern "C" DLL_EXPORT bool	 Print3(char* pp, int type);
long printNew_1(string pp, LONG nPrintType);
long printNew3(string pp, LONG nPrintType);