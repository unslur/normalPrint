#include "stdfx.h"
#include "Funcs.h"



//extern char  DBPathName[40]={"d:\\zyczs\\tcm.db" };





void splitStrTwo( string printStr, string &Str1, string &Str2 )
{

	int b = printStr.find("|");
	if( b != -1 ){
		Str1 = printStr.substr(0,b);
		Str2 = printStr.substr(b+1,printStr.length());
	}
	else{
		if(printStr.length()!=0){
			Str1 = printStr;
		}
	}

	return;
}

list<string> splitPrintStr( string printStr ){
	list<string> vstr;
	while (true){
		int b = printStr.find("^");
		if( b != -1 ){
			vstr.push_back(printStr.substr(0,b));
			printStr = printStr.substr(b+1,printStr.length());
		}
		else{
			if(printStr.length()!=0){
				vstr.push_back(printStr);
			}
			break;
		}
	}
	return vstr;
}
list<string> splitPrintStr2( string printStr,char * Cnum ){
	list<string> vstr;
	while (true){
		int b = printStr.find(Cnum[0]);
		if( b != -1 ){
			vstr.push_back(printStr.substr(0,b));
			printStr = printStr.substr(b+1,printStr.length());
		}
		else{
			if(printStr.length()!=0){
				vstr.push_back(printStr);
			}
			break;
		}
	}
	return vstr;
}
vector<string> VsplitPrintStr(string printStr) {
	vector<string> vstr;
	while (true) {
		int b = printStr.find("#");
		if (b != -1) {
			vstr.push_back(printStr.substr(0, b));
			printStr = printStr.substr(b + 1, printStr.length());
		}
		else {
			if (printStr.length() != 0) {
				vstr.push_back(printStr);
			}
			break;
		}
	}
	return vstr;
}

void splitStrThree( string printStr, string &Str1, string &Str2, string&Str3 ){

	string strTemp;

	int b = printStr.find("|");
	if( b != -1 ){
		Str1 = printStr.substr(0,b);
		strTemp = printStr.substr(b+1,printStr.length());
		b = 0;
		b = strTemp.find("|");

		if (b != -1) {
			Str2 = strTemp.substr(0, b);
			Str3 = strTemp.substr(b+1,strTemp.length());
		}
		else {
			if(printStr.length()!=0){
				Str2 = strTemp;
			}
		}
	}
	else{
		if(printStr.length()!=0){
			Str1 = printStr;
		}
	}

	return;
}

//#define DYJC 34

list<string> splitPrintv( list<string>& printStrv, int DYJC ){
	list<string> vstr;
	for(list<string>::const_iterator iter = printStrv.begin(); iter != printStrv.end();++iter){
		string tstr = *iter; //GBK 前字81-FE 之间，尾字节在 40-FE
		while(true){
			if(tstr.length()<=DYJC){
				vstr.push_back(tstr);
				break;
			}
			bool f = false;
			for( int i = 0; i < DYJC;){
				char m = tstr.at(i);
				if( unsigned(m) < 0x80 ){
					f = true;
					i++;
				}
				else{
					i += 2;
					if(i%2==0){
						f = true;
					}else{
						f = false;
					}
				}
			}
			if(f){
				vstr.push_back(tstr.substr(0,DYJC));
				tstr = tstr.substr(DYJC,tstr.length());
			}
			else{
				vstr.push_back(tstr.substr(0,DYJC-1));
				tstr = tstr.substr(DYJC-1,tstr.length());
			}
		}
	}
	return vstr;
}


list<string> splitPrintv( string& tstr, int DYJC ){
	list<string> vstr;
	while(true){
		if(tstr.length()<=DYJC){
			vstr.push_back(tstr);
			break;
		}
		bool f = false;
		for( int i = 0; i < DYJC;){
			char m = tstr.at(i);
			if( unsigned(m) < 0x80 ){//汉字第一个字节在）0x81-0xFE之间 ，
				f = true;
				i++;
			}
			else{
				i += 2;
				if(i%2==0){
					f = true;
				}else{
					f = false;
				}
			}
		}
		if(f){
			vstr.push_back(tstr.substr(0,DYJC));
			tstr = tstr.substr(DYJC,tstr.length());
		}
		else{
			vstr.push_back(tstr.substr(0,DYJC-1));
			tstr = tstr.substr(DYJC-1,tstr.length());
		}
	}
	return vstr;
}

char* Gb2312ToUtf8(const char *pcGb2312) /*const*/
{
	int nUnicodeLen = MultiByteToWideChar(CP_ACP, 0, pcGb2312, -1, NULL, 0);

	wchar_t * pcUnicode = new wchar_t[nUnicodeLen+1]; 
	memset(pcUnicode, 0, nUnicodeLen * 2 + 2); 

	MultiByteToWideChar(CP_ACP, 0, pcGb2312, -1, pcUnicode, nUnicodeLen);

	int nUtf8Len = WideCharToMultiByte(CP_UTF8, 0, pcUnicode, -1, NULL, 0, NULL, NULL);

	char *pcUtf8=new char[nUtf8Len + 1]; 
	memset(pcUtf8, 0, nUtf8Len + 1);   

	WideCharToMultiByte(CP_UTF8, 0, pcUnicode, -1, pcUtf8, nUtf8Len, NULL, NULL);

	delete[] pcUnicode; 
	return pcUtf8;
}
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
void delchar(char * str,char CharNum){
	char *d = str;
	while (*str != '\0') {
			
		if (*str != CharNum) {
			*d++ = *str;
		}
			
		++str;
		
	}
	*d = '\0';
	
}