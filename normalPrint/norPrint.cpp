#include "norPrint.h"
using namespace std;
#include <string>
#include <iostream> 
#include <windows.h>
#include <comutil.h>
DLL_EXPORT bool Print2(char* pp, int type)
{
	MessageBox(NULL, "4", NULL, MB_OK);
	int rtn=printNew_1(pp,type);
	if (rtn!=1)
	{
		return false;
	}
	return true;
}

DLL_EXPORT bool Print3(char* pp, int type)
{
	int rtn=printNew3(pp, type);
	if (rtn != 1)
	{
		return false;
	}
	return true;
}
const  string DefaultPrinter()
{
	TCHAR szBuffer[1024] = { 0 };
	DWORD length = 1024;
	int ret = ::GetDefaultPrinter(szBuffer, &length);

	return szBuffer;
}

long printNew_1(string pp,  LONG nPrintType)
{
	string printStr = pp;
	int rtn = 0;

	char printerName[0x64] = { 0 };
	strcpy(printerName, DefaultPrinter().c_str());
	//MessageBox(NULL, "1", NULL, MB_OK);
	if (strstr(printerName, "TSC") != NULL
		|| strstr(printerName, "Printer B") != NULL)
	{
		CTscPrinter printer;
		//MessageBox(NULL, "2", NULL, MB_OK);
		if (printer.TscInit(printerName) == false) {
			
			return 0;
		}
		//MessageBox(NULL, "3", NULL, MB_OK);
		rtn = printer.PrintTsc2_1(NULL, printStr, nPrintType);
		printer.TscUnInit();
	}
	else if (strstr(printerName, "POSTEK") != NULL)
	{
		CPskPrinter printer;
		if (!printer.PskInit(printerName))
		{
			MessageBox(NULL, "请检查是否连接打印机！", NULL, MB_OK);
			return 0;
		}

		rtn = printer.PrintPsk2_1(NULL, printStr, nPrintType);
		printer.PskUnInit();
	}
	else if (strstr(printerName, "ZDesigner") != NULL || strstr(printerName, "Microsoft") != NULL)
	{
		CZbraPrinter printer;
		rtn = printer.PrintZbra2_1(printerName, printStr, nPrintType);
	}
	else
	{

		MessageBox(NULL, "请检查是否正确设置默认打印机！", NULL, MB_OK);
	}
	return rtn;
}
long printNew3(string pp,  LONG nPrintType)
{
	string printStr = pp;
	int rtn = 0;

	char printerName[0x64] = { 0 };
	strcpy(printerName, DefaultPrinter().c_str());

	if (strstr(printerName, "Printer LP") != NULL
		|| strstr(printerName, "Printer B") != NULL)
	{
		CTscPrinter printer;
		printer.TscInit(printerName);

		rtn = printer.PrintTsc3(NULL, printStr, nPrintType);
		printer.TscUnInit();
	}
	else if (strstr(printerName, "POSTEK") != NULL)
	{
		CPskPrinter printer;
		printer.PskInit(printerName);
		rtn = printer.PrintPsk3(NULL, printStr, nPrintType);
		printer.PskUnInit();
	}
	else if (strstr(printerName, "ZDesigner") != NULL || strstr(printerName, "Microsoft") != NULL)
	{
		CZbraPrinter printer;
		rtn = printer.PrintZbra3(printerName, printStr, nPrintType);
	}
	else
	{
		MessageBox(NULL, "请检查是否正确设置默认打印机！", NULL, MB_OK);
	}
	return rtn;

}