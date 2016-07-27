#include "stdfx.h"
#include ".\tscprinter.h"

HINSTANCE gt1Tsc;
fTSC_Openport TSC_Openport=NULL;
fTSC_Closeport TSC_Closeport=NULL;
fTSC_Sendcommand TSC_Sendcommand=NULL;
fTSC_Setup TSC_Setup=NULL;
fTSC_Clearbuffer TSC_Clearbuffer=NULL;
fTSC_Printlabel TSC_Printlabel=NULL;
fTSC_Windowsfont TSC_Windowsfont=NULL;

CTscPrinter::CTscPrinter(void)
{
	wineFlag = false;
}

CTscPrinter::~CTscPrinter(void)
{
}

bool CTscPrinter::printNew2_tsc_1(const string& printStr,int X, int Y,fTSC_Sendcommand TSC_DrawQR,fTSC_Windowsfont TSC_DrawText)
{
	char buff[0x100];
	list<string> printv = splitPrintStr(printStr);
	int  ret = 0,z=0;
	int M =496+X;
	int N =140+Y;
	char xbuf[8]={0};
	char ybuf[8]={0};
	string qr_param = "";
	int len = 0;
	//MessageBox(NULL, "6", NULL, MB_OK);
	for ( list<string>::iterator iter = printv.begin();iter != printv.end(); ++iter ){
		
		if( 0 == z ){ //打二维码
			len = (int)strlen((char *)iter->c_str());
			if ( 0 == len)
			{
				break;
			}
			sprintf(xbuf,"%d",M-8);
			sprintf(ybuf,"%d",N+8);
			qr_param = "QRCODE ";
			qr_param += xbuf;
			qr_param += ",";
			qr_param += ybuf;


			if (strstr(iter->c_str(),"http") != NULL)
			{
				qr_param += ",L,3,A,180,M2,S2,\"";
			}
			else
				qr_param += ",Q,3,A,180,M2,S2,\"";

			
			qr_param += (char *)iter->c_str();
			qr_param += "\"";
			ret = TSC_DrawQR((char *)qr_param.c_str());
			if ( ret != 1 ){
				sprintf(buff,"TSC_DrawQR:%d",ret);
				throw(buff);
			}
			
		}else if( 1 == z ){//打数字码
			*iter=iter->substr((iter->find( "溯源码:")!=-1?iter->find("溯源码:")+7:0),iter->length());
			list<string> printCodes = splitPrintv(iter->substr(0,50),16);
			int n=N-92;
			
			for ( list<string>::const_iterator citer = printCodes.begin(); citer != printCodes.end(); ++citer ){
				ret = TSC_DrawText(M-7,n,12,180,2,0,"宋体",(char *)citer->c_str());
				if ( ret != 1 ){
					sprintf(buff,"TSC_DrawText:%d",ret);
					throw(buff);
				}
				n-=14;
				
			}
			
			// DelRecordByCode(iter->c_str(),DBPathName);
			
		}else if( 2 == z || 4 == z || 6 == z || 7 == z || 3 == z || 5 == z){ //品名 产地 批号 厂家	
			if (iter->length()==0)
			{
				z++;
				continue;
			}	
			if( 7 == z&&(iter->length()>23)){
				delchar((char *)iter->c_str(),' ');
			*iter=iter->substr((iter->find( "厂家:")!=-1?iter->find("厂家:")+5:0),iter->length());
			list<string> printcomp = splitPrintv(*iter,20);
			for ( list<string>::const_iterator citer = printcomp.begin(); citer != printcomp.end(); ++citer ){
				//MessageBox(NULL,citer->c_str(),NULL,MB_OK);
				ret = TSC_DrawText(M+160,N-8,14,180,2,0,"宋体",(char *)citer->c_str());
				if ( ret != 1 ){
					sprintf(buff,"TSC_DrawText:%d",ret);
					throw(buff);
				}
				N-=18;

			}
				}
			else
			{
				ret = TSC_DrawText(M+160,N-8,14,180,2,0,"宋体",(char *)iter->c_str());
				if ( ret != 1 ){
					sprintf(buff,"TSC_DrawText:%d",ret);
					throw(buff);
				}
				N -= 18; 
			}
		}
#if 0


		else if( 3 == z || 5 == z ){ //重量  生产日期
			ret = TSC_DrawText(XX,y,16,180,2,0,"雅黑",(char *)iter->c_str());
			if ( ret != 1 ){
				sprintf(buff,"TSC_DrawText:%d",ret);
				throw(buff);
			}
			y -= 22;
		}
#endif
		z++;
	}
	//MessageBox(NULL, "7", NULL, MB_OK);
	return true;
}

bool CTscPrinter::printNew2_tsc(const string& printStr,int X, int Y,fTSC_Sendcommand TSC_DrawQR,fTSC_Windowsfont TSC_DrawText)
{
	char buff[0x100];
	//AfxMessageBox(printStr.c_str());
	int offsetX=0,offsetY=0;
	list<string> printv = splitPrintStr(printStr);
	int x = 0, y = 0, z = 0, ret = 0,XX = X - 135;
	char xbuf[8]={0};
	char ybuf[8]={0};
	string qr_param = "";
	int len = 0;
	for ( list<string>::iterator iter = printv.begin();iter != printv.end(); ++iter ){
			
		if( 0 == z ){ //打二维码
			if (iter->length()==0)
			{
				break;
			}
			sprintf(xbuf,"%d",X-134+12);
			sprintf(ybuf,"%d",Y);
			qr_param = "QRCODE ";
			qr_param += xbuf;
			qr_param += ",";
			qr_param += ybuf;
			
			
			if (strstr(iter->c_str(),"http") != NULL)
			{
				qr_param += ",Q,4,A,180,M2,S2,\"";	
			
			}else
				qr_param += ",Q,5,A,180,M2,S2,\"";


			qr_param += (char *)iter->c_str();
			qr_param += "\"";
			ret = TSC_DrawQR((char *)qr_param.c_str());
			if ( ret != 1 ){
				sprintf(buff,"TSC_DrawQR:%d",ret);
				throw(buff);
			}
			
			y = Y - 170;
			
		}else if( 1 == z ){//打数字码
			if (iter->length()==0)
			{
				z++;
				continue;
			}
			list<string> printCodes = splitPrintv(string(*iter),28);
			int x = X+4-10;
			for ( list<string>::const_iterator citer = printCodes.begin(); citer != printCodes.end(); ++citer ){
				ret = TSC_DrawText(x,y,15,180,2,0,"宋体",(char *)citer->c_str());
				if ( ret != 1 ){
					sprintf(buff,"TSC_DrawText:%d",ret);
					throw(buff);
				}
				x -= 58;
				y -= 22;
			}
			*iter=iter->substr((iter->find( "溯源码:")!=-1?iter->find("溯源码:")+7:0),iter->length());
			
			//string trn=	DelRecordByCode(iter->c_str(),DBPathName);
		
		}else if( 2 == z || 4 == z || 6 == z || 7 == z||3 == z || 5 == z  ){ //品名 产地 批号 厂家
			if( 3 == z){
				delchar((char *)iter->c_str(),' ');
			}
			if (iter->length()==0)
			{
				z++;
				continue;
			}
			ret = TSC_DrawText(X+4-10,y,15,180,2,0,"宋体",(char *)iter->c_str());
			if ( ret != 1 ){
				sprintf(buff,"TSC_DrawText:%d",ret);
				throw(buff);
			}
			
				y -= 20;
		}
		
		z++;
	}
	return true;
}
bool CTscPrinter::printNew2_tsc_tag(const string& printStr,int X, int Y,fTSC_Sendcommand TSC_DrawQR,fTSC_Windowsfont TSC_DrawText)
{
	char buff[0x100];
	list<string> printv = splitPrintStr(printStr);
	char xbuf[8]={0};
	char ybuf[8]={0};
	int ret;
	string qr_param = "";
	int len = 0;
	int z = 0;
	for ( list<string>::iterator iter = printv.begin();iter != printv.end(); ++iter ){
		len = (int)strlen((char *)iter->c_str());
		if ( 0 == len)
		{
			if (11 == z)//11为质检员位置，横移
			{
				X-=176;
			}
			else
			{
				Y-=52;
			}
			z++;
			continue;
		}
		if( 0 == z ){ //打二维码
			sprintf(xbuf,"%d",X-240);
			sprintf(ybuf,"%d",Y-80);
			qr_param = "QRCODE ";
			qr_param += xbuf;
			qr_param += ",";
			qr_param += ybuf;

			
			if (strstr(iter->c_str(),"http") != NULL)
			{
				qr_param += ",L,3,A,180,M2,S2,\"";
			}else if (strlen(iter->c_str())<5)
			{
				break;
			}
			else
				qr_param += ",Q,3,A,180,M2,S2,\"";


			qr_param += (char *)iter->c_str();
			qr_param += "\"";
			ret = TSC_DrawQR((char *)qr_param.c_str());
			if ( ret != 1 ){
				sprintf(buff,"TSC_DrawQR:%d",ret);
				throw(buff);}
			
		}else if( 1 == z ){//打数字码
			
			int y=Y-184;
			list<string> printCodes = splitPrintv(string(*iter),12);
			for ( list<string>::const_iterator citer = printCodes.begin(); citer != printCodes.end(); ++citer ){
				ret = TSC_DrawText(X-240,y,13,180,2,0,"宋体",(char *)citer->c_str());
				if ( ret != 1 ){
					sprintf(buff,"TSC_DrawText:%d",ret);
					throw(buff);
				}
				y-=16;
			}
			*iter=iter->substr((iter->find( "溯源码:")!=-1?iter->find("溯源码:")+7:0),iter->length());

			//DelRecordByCode(iter->c_str(),DBPathName);
			
		}
		else if( 5 == z ){ //生产企业
			ret = TSC_DrawText(X-100,Y-105,17,180,2,0,"宋体",(char *)iter->c_str());
			if ( ret != 1 )
			{
				sprintf(buff,"TSC_DrawText:%d",ret);
				throw(buff);
			}
			if(11 == z)//11为质检员位置，横移
			{
				X-=176;
			}
			else
			{
				Y -= 54;
			}

		}
		///
		//某企业 修改排版
		//
		///
		//else if( 5 == z ){ //生产企业
		//	ret = TSC_DrawText(X-100,Y-105-3*54,17,180,2,0,"宋体",(char *)iter->c_str());
		//	if ( ret != 1 )
		//	{
		//		sprintf(buff,"TSC_DrawText:%d",ret);
		//		throw(buff);
		//	}
		//	if(11 == z)//11为质检员位置，横移
		//	{
		//		X-=176;
		//	}
		//	else
		//	{
		//		Y -= 54;
		//	}

		//}
		//else if( 6 == z ){ //执行标准
		//	ret = TSC_DrawText(X-100,Y-105-3*54,22,180,2,0,"宋体",(char *)iter->c_str());
		//	if ( ret != 1 )
		//	{
		//		sprintf(buff,"TSC_DrawText:%d",ret);
		//		throw(buff);
		//	}
		//	if(11 == z)//11为质检员位置，横移
		//	{
		//		X-=176;
		//	}
		//	else
		//	{
		//		Y -= 54;
		//	}

		//}
		//else if( 7 == z ){ //生产批号
		//	ret = TSC_DrawText(X-100,Y-105+1*54,22,180,2,0,"宋体",(char *)iter->c_str());
		//	if ( ret != 1 )
		//	{
		//		sprintf(buff,"TSC_DrawText:%d",ret);
		//		throw(buff);
		//	}
		//	if(11 == z)//11为质检员位置，横移
		//	{
		//		X-=176;
		//	}
		//	else
		//	{
		//		Y -= 54;
		//	}

		//}
		//else if( 8 == z ){ //生产日期
		//	ret = TSC_DrawText(X-100,Y-105+1*54,22,180,2,0,"宋体",(char *)iter->c_str());
		//	if ( ret != 1 )
		//	{
		//		sprintf(buff,"TSC_DrawText:%d",ret);
		//		throw(buff);
		//	}
		//	if(11 == z)//11为质检员位置，横移
		//	{
		//		X-=176;
		//	}
		//	else
		//	{
		//		Y -= 54;
		//	}

		//}
		//else if( 9 == z ){ //净重
		//	ret = TSC_DrawText(X-100,Y-105+4*54,22,180,2,0,"宋体",(char *)iter->c_str());
		//	if ( ret != 1 )
		//	{
		//		sprintf(buff,"TSC_DrawText:%d",ret);
		//		throw(buff);
		//	}
		//	if(11 == z)//11为质检员位置，横移
		//	{
		//		X-=176;
		//	}
		//	else
		//	{
		//		Y -= 54;
		//	}

		//}
		else { 
				ret = TSC_DrawText(X-100,Y-105,22,180,2,0,"宋体",(char *)iter->c_str());
				if ( ret != 1 )
				{
					sprintf(buff,"TSC_DrawText:%d",ret);
					throw(buff);
				}
				if(11 == z)//11为质检员位置，横移
				{
					X-=176;
				}
				else
				{
					Y -= 54;
				}
			
		}
		z++;
	}
	return true;
}
bool CTscPrinter::printNew3_tsc(const string& printStr,int X, int Y,fTSC_Sendcommand TSC_DrawQR,fTSC_Windowsfont TSC_DrawText)
{
	char buff[0x100];
	list<string> printv = splitPrintStr(printStr);
	int y = 0,z = 0,ret = 0;
	char xbuf[8]={0};
	char ybuf[8]={0};
	string qr_param = "";
	int len = 0;
	bool flag = false;
	int division=12;
	int offset_X=0,offset_Y=0;
	for ( list<string>::iterator iter = printv.begin();iter != printv.end(); ++iter ){
		
		if( 0 == z ){ //打二维码

			len = (int)strlen((char *)iter->c_str());
			if ( 0 == len)
			{
				break;
			}			
			//printf("%d",10);
			sprintf(xbuf,"%d",X-96);
			sprintf(ybuf,"%d",Y+8);
			
			qr_param = "QRCODE ";
			qr_param += xbuf;
			qr_param += ",";
			qr_param += ybuf;
			
			//if (wineFlag)
			if (strstr(iter->c_str(),"http") != NULL)
			{
				qr_param += ",L,3,A,180,M2,S3,\"";//L代表纠错能力 L 7%， M 15%， Q 25%，H 30% 纠错能力越大 二维码便越大，为了能提高扫描成功率，考虑纸张大小，故选取L 与三倍的组合
			}
			else
				qr_param += ",M,4,A,180,M2,S2,\"";
			
			qr_param += (char *)iter->c_str();
			qr_param += "\"";
			ret = TSC_DrawQR((char *)qr_param.c_str());
			if ( ret != 1 ){
				sprintf(buff,"TSC_DrawQR:%d",ret);
				throw(buff);
			}
			
			y=Y-95;
		}else if( 1 == z ){//打数字码
			*iter=iter->substr((iter->find( "溯源码:")!=-1?iter->find("溯源码:")+7:0),iter->length());
			if (iter->c_str()[0]=='8')
			{
				division=20;
				offset_X=110-14;offset_Y=-32;
			}
			list<string> printCodes = splitPrintv(string(*iter),division);
			for ( list<string>::const_iterator citer = printCodes.begin(); citer != printCodes.end(); ++citer ){
				
				ret = TSC_DrawText(X-98+offset_X,y,14,180,2,0,"宋体",(char *)citer->c_str());
				if ( ret != 1 ){
					sprintf(buff,"TSC_DrawText:%d",ret);
					throw(buff);
				}
				y -= 15;
			}
			if (iter->c_str()[0]=='6')
			{
				offset_Y=15;

			}
			
			 y = Y - 95+offset_Y;
			*iter=iter->substr((iter->find( "溯源码:")!=-1?iter->find("溯源码:")+7:0),iter->length());

			 //DelRecordByCode(iter->c_str(),DBPathName);
			
		}
		else{//其它文字
			
			if (2 == z)
			{
				delchar((char*)iter->c_str(),' ');
			}
			if (iter->length()==0)
			{
				z++;
				continue;
			}
			ret = TSC_DrawText(X,y,14,180,2,0,"宋体",(char *)iter->c_str());	
			if ( ret != 1 ){
				sprintf(buff,"TSC_DrawText:%d",ret);
				throw(buff);
			}
			y -= 15;
		}
		z++;
	}
	return true;
}
bool CTscPrinter::printNewWhite_tsc(const string& printStr,int X, int Y,fTSC_Sendcommand TSC_DrawQR,fTSC_Windowsfont TSC_DrawText)
{
	char buff[0x100];
	list<string> printv = splitPrintStr(printStr);
	int y = Y-50,z = 0,ret = 0;
	char xbuf[8]={0};
	char ybuf[8]={0};
	string qr_param = "";
	int len = 0;
	bool flag = false;
	int division=12;
	int offset_X=0,offset_Y=0;
	for ( list<string>::iterator iter = printv.begin();iter != printv.end(); ++iter ){		
		ret = TSC_DrawText(X,y,14,180,2,0,"宋体",(char *)iter->c_str());	
		if ( ret != 1 ){
			sprintf(buff,"TSC_DrawText:%d",ret);
			throw(buff);
		}
		y -= 30;
		
		z++;
	}
	return true;
}
void DwordToString(string &outstr, DWORD dwValue)
{

	char szHex[10];
	char chrTmp[] = "0123456789ABCDEF";
	/*if(sizeof(szHex) < 10)
	return;*/
	szHex[0] = '0';
	szHex[1] = 'x';

	for (int i = 0; i < 8; i++)
		szHex[2 + i] = *(chrTmp + (((dwValue) >> (28 - i * 4)) & 0xF));

	outstr = szHex;
}
bool CTscPrinter::TscInit(char* printerName)
{
	gt1Tsc = LoadLibrary("TSCLIB.dll");
	if(!gt1Tsc){
		DWORD er = GetLastError();
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		//DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			er,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		MessageBox(NULL, (LPCSTR)lpMsgBuf, NULL, MB_OK);
		return false;
	}
	TSC_Openport = (fTSC_Openport)GetProcAddress(gt1Tsc,"openport");
	TSC_Closeport = (fTSC_Closeport)GetProcAddress(gt1Tsc,"closeport");
	TSC_Sendcommand = (fTSC_Sendcommand)GetProcAddress(gt1Tsc,"sendcommand");
	TSC_Setup = (fTSC_Setup)GetProcAddress(gt1Tsc,"setup");
	TSC_Clearbuffer = (fTSC_Clearbuffer)GetProcAddress(gt1Tsc,"clearbuffer");
	TSC_Printlabel = (fTSC_Printlabel)GetProcAddress(gt1Tsc,"printlabel");
	TSC_Windowsfont = (fTSC_Windowsfont)GetProcAddress(gt1Tsc,"windowsfont");
	if (!TSC_Openport||!TSC_Closeport||!TSC_Sendcommand||!TSC_Setup||!TSC_Clearbuffer||!TSC_Printlabel||!TSC_Windowsfont)
	{
		MessageBox(NULL, "调用tsclib.dll函数错误", NULL, MB_OK);
		return false;
	}

	int ret = TSC_Openport(printerName);	
	if ( ret != 1 ){
		MessageBox(NULL, "打开端口错误", NULL, MB_OK);
		return false;
	}
	return true;
}
bool CTscPrinter::TscUnInit()
{
	TSC_Closeport();
    FreeLibrary(gt1Tsc);
	
	return true;
}

int CTscPrinter::PrintTsc2(char* printerName,const string& printStr,LONG nPrintType)
{
	int rtn;
	
	char buff[0x100]={0};
	string printStr1, printStr2;
	splitStrTwo(printStr, printStr1, printStr2);
	
	
	
	try{
		int ret = TSC_Setup("85","45","3","10","0","5","0");

		TSC_Sendcommand("SET CUTTER OFF");
		TSC_Sendcommand("DIRECTION 1");
#if 1
		ret = TSC_Clearbuffer();
		if ( ret != 1 ){
			sprintf(buff,"TSC_Clearbuffer:%d",ret);
			throw(buff);
		}
#endif
		//int X = 80,Y = 23;
		int X = 662,Y = 360;
		//打印左边
		if (printStr1.length() > 0 && (nPrintType == 1 || nPrintType == 3)){//
			/*bIsPrint |= */printNew2_tsc(printStr1,X,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//打印右边
		if (printStr2.length() > 0 && (nPrintType == 2 || nPrintType == 3)){
			/*bIsPrint |= */printNew2_tsc(printStr2,X-=362,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//==================================
		ret = TSC_Printlabel("1", "1");	
		if ( ret != 1 ){
			sprintf(buff,"PTK_PrintLabel:%d",ret);
			throw(buff);
		}
		//TSC_Closeport();
		rtn = 1;
	}
	catch (const exception& e) {
		MessageBox(NULL,e.what(),NULL,MB_OK);
		rtn = 0;
	}
	catch (...) {
		//sprintf(buff,"打印机错误:%d",GetLastError());
		MessageBox(NULL, buff, NULL, MB_OK);
		rtn = 0;
	}
	//FreeLibrary(gt1);
	return rtn;
}
//extern int countnum;
int CTscPrinter::PrintTscTag2(char* printerName,const string& printStr,LONG nPrintType)
{
	int rtn;

	char buff[0x100]={0};
	string printStr1, printStr2;
	splitStrTwo(printStr, printStr1, printStr2);

	try{
		int ret = TSC_Setup("100","80","3","10","0","2","0");

		TSC_Sendcommand("SET CUTTER OFF");
		TSC_Sendcommand("DIRECTION 1");
		ret = TSC_Clearbuffer();
		if ( ret != 1 ){
			sprintf(buff,"TSC_Clearbuffer:%d",ret);
			throw(buff);
		}

		
		int X = 800,Y = 640;
		//打印左边
		//countnum++;
		if (printStr1.length() > 0 && (nPrintType == 1 || nPrintType == 3)){
			printNew2_tsc_tag(printStr1,X,Y,TSC_Sendcommand,TSC_Windowsfont);
		}
		//打印右边
		if (printStr2.length() > 0 && (nPrintType == 2 || nPrintType == 3)){
			printNew2_tsc_tag(printStr2,X-=408,Y,TSC_Sendcommand,TSC_Windowsfont);
		}
		//countnum++;
		//==================================
		
		ret = TSC_Printlabel("1","1");
		if ( ret != 1 ){
			sprintf(buff,"ptk_printlabel:%d",ret);
			throw(buff);
		}
		
		rtn = 1;
	}
	catch (const exception& e) {
		MessageBox(NULL, e.what(), NULL, MB_OK);
		rtn = 0;
	}
	catch (...) {
		//sprintf(buff,"打印机错误:%d",GetLastError());
		MessageBox(NULL, buff, NULL, MB_OK);
		rtn = 0;
	}
	//FreeLibrary(gt1);
	return rtn;
}
int CTscPrinter::PrintTsc2_1(char* printerName,const string& printStr,LONG nPrintType)
{
	int rtn;

	char buff[0x100]={0};
	string printStr1, printStr2;
	splitStrTwo(printStr, printStr1, printStr2);
	//MessageBox(NULL, "4", NULL, MB_OK);
	try{
		int ret = TSC_Setup("85","30","3","10","0","5","0");
#if 1
		ret = TSC_Clearbuffer();
		if ( ret != 1 ){
			sprintf(buff,"TSC_Clearbuffer:%d",ret);
			throw(buff);
		}
#endif
		TSC_Sendcommand("SET CUTTER OFF");
		TSC_Sendcommand("DIRECTION 1");

		//int X = 80,Y = 23;
		int X = 4,Y = 0;
		//打印左边
		//countnum++;
		//MessageBox(NULL, "5", NULL, MB_OK);
		if (printStr1.length() > 0 && (nPrintType == 1 || nPrintType == 3)){
			/*bIsPrint |= */printNew2_tsc_1(printStr1,X,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//打印右边
#if 1
		//countnum++;

		if (printStr2.length() > 0 && (nPrintType == 2 || nPrintType == 3)){
			/*bIsPrint |= */printNew2_tsc_1(printStr2,X-=360,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
#endif		//==================================
		ret = TSC_Printlabel("1", "1");	
		if ( ret != 1 ){
			sprintf(buff,"PTK_PrintLabel:%d",ret);
			throw(buff);
		}
		//TSC_Closeport();
		rtn = 1;
	}
	catch (const exception& e) {
		MessageBox(NULL, e.what(), NULL, MB_OK);
		rtn = 0;
	}
	catch (...) {
		//sprintf(buff,"打印机错误:%d",GetLastError());
		MessageBox(NULL, buff, NULL, MB_OK);
		rtn = 0;
	}
	//FreeLibrary(gt1);
	return rtn;
}
int CTscPrinter::PrintTsc3(char* printerName,const string& printStr,LONG nPrintType)
{
	int rtn;
	bool bIsPrint = false;
	char buff[0x100]={0};
	string printStr1, printStr2,printStr3;
	splitStrThree(printStr, printStr1, printStr2, printStr3);

	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try{
		
		int ret = TSC_Setup("95","25","3","10","0","3","2");
		
		ret = TSC_Clearbuffer();
		if ( ret != 1 ){
			sprintf(buff,"PTK_ClearBuffer:%d",ret);
			throw(buff);
		}
		
		TSC_Sendcommand("SET CUTTER OFF");
		TSC_Sendcommand("DIRECTION 1");

		//int X = 25,Y = 10;
		int X = 738,Y = 172;
		//打印左边
		
		if (printStr1.length() > 0 && (nPrintType == 1 || nPrintType == 4)){
			bIsPrint |= printNew3_tsc(printStr1,X,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//打印中间
		if (printStr2.length() > 0 && (nPrintType == 2 || nPrintType == 4)){
			bIsPrint |= printNew3_tsc(printStr2,X-=260,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//打印右边
		if (printStr3.length() > 0 && (nPrintType == 3 || nPrintType == 4)){
			bIsPrint |= printNew3_tsc(printStr3,X-=260,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		
		//==================================
		if (bIsPrint){
			ret = TSC_Printlabel("1", "1");	
			if ( ret != 1 ){
				sprintf(buff,"TSC_Printlabel:%d",ret);
				throw(buff);
			}
		}
		//TSC_Closeport();
		rtn = 1;
	}
	catch (const exception& e) {
		MessageBox(NULL, e.what(), NULL, MB_OK);
		rtn = 0;
	}
	catch (...) {
		//sprintf(buff,"打印机错误:%d",GetLastError());
		MessageBox(NULL, buff, NULL, MB_OK);
		rtn = 0;
	}
	//FreeLibrary(gt1);
	return rtn;
}
int CTscPrinter::PrintTscWhite(char* printerName,const string& printStr,LONG nPrintType)
{
	int rtn;
	bool bIsPrint = false;
	char buff[0x100]={0};
	string printStr1, printStr2,printStr3;
	splitStrThree(printStr, printStr1, printStr2, printStr3);

	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try{
		int ret = TSC_Setup("100","25","3","10","0","2","2");
		ret = TSC_Clearbuffer();
		if ( ret != 1 ){
			sprintf(buff,"PTK_ClearBuffer:%d",ret);
			throw(buff);
		}
		TSC_Sendcommand("SET CUTTER OFF");
		TSC_Sendcommand("DIRECTION 1");

		//int X = 25,Y = 10;
		int X = 738,Y = 172;
		//打印左边
		if (printStr1.length() > 0 && (nPrintType == 1 || nPrintType == 4)){
			bIsPrint |= printNewWhite_tsc(printStr1,X,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//打印中间
		if (printStr2.length() > 0 && (nPrintType == 2 || nPrintType == 4)){
			bIsPrint |= printNewWhite_tsc(printStr2,X-=276,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//打印右边
		if (printStr3.length() > 0 && (nPrintType == 3 || nPrintType == 4)){
			bIsPrint |= printNewWhite_tsc(printStr3,X-=276,Y,/*id_name,*/TSC_Sendcommand,TSC_Windowsfont);
		}
		//==================================
		if (bIsPrint){
			ret = TSC_Printlabel("1", "1");	
			if ( ret != 1 ){
				sprintf(buff,"TSC_Printlabel:%d",ret);
				throw(buff);
			}
		}
		//TSC_Closeport();
		rtn = 1;
	}
	catch (const exception& e) {
		MessageBox(NULL, e.what(), NULL, MB_OK);
		rtn = 0;
	}
	catch (...) {
		//sprintf(buff,"打印机错误:%d",GetLastError());
		MessageBox(NULL, buff, NULL, MB_OK);
		rtn = 0;
	}
	//FreeLibrary(gt1);
	return rtn;
}
