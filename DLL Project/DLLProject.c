#include "excelreport.h"
#include <rs232.h>
#include <ansi_c.h>
#include <userint.h>
#include "DLLProject.h"


void UpdateLogDLL(int data,unsigned char cmd,char *stringPrint,char *Date_string)
{
	switch (cmd)
	{
		case 'C':
			sprintf(stringPrint,"%s --> COM Port %d Connected \n",Date_string,data);
			break;
		case 'S':
			sprintf(stringPrint,"%s --> Water Level %d cm Pump OFF \n",Date_string,data);
			break;
		case 'F':
			sprintf(stringPrint,"%s --> Water Level %d cm Pump ON \n",Date_string,data);
			break;
		case 'D':
			sprintf(stringPrint,"%s --> Disconnected \n",Date_string);
			break;
		case 'U':
			sprintf(stringPrint,"%s --> UP Limit Changed To %d cm \n",Date_string,data);
			break;
		case 'L':
			sprintf(stringPrint,"%s --> DOWN Limit Changed To %d cm \n",Date_string,data);
			break;
		case 'A':
			sprintf(stringPrint,"%s --> LOG Saved Successfully \n",Date_string);		
			break;
		case 'B':
			sprintf(stringPrint,"%s --> Data Saved Successfully \n",Date_string);		
			break;
		default:
			break;
	}
}
void sendAlert(char cmd,int com)
{
	char str[3];
	//char pump;
	sprintf(str,"%c\n",cmd);
	if (ComWrt (com, str, strlen(str)) != strlen(str))
	{
		MessagePopup ("Connection Error", "Failed to Send Data");
	}
	
	return;
}

void SaveXLSX(struct datastr Data)
{
	

	static CAObjHandle excelworkbook;
	static CAObjHandle excelapphandle;
	static CAObjHandle Sheethandle;
	double time[SIZE]={0.0},data[SIZE]={0.0},UpLimit[SIZE]={0.0},LowLimit[SIZE]={0.0};
	for (int i = 0; i<SIZE;i++)
			{
				time[i]= (double)Data.time[i];
				data[i]=(double)Data.data[i];
				UpLimit[i]=(double)Data.UpLimit[i];
				LowLimit[i]=(double)Data.LowLimit[i];
			}
			ExcelRpt_ApplicationNew(VTRUE,&excelapphandle);
			ExcelRpt_WorkbookNew(excelapphandle,&excelworkbook);
			
			ExcelRpt_GetWorksheetFromIndex (excelworkbook, 1, &Sheethandle);
			ExcelRpt_SetWorksheetAttribute(Sheethandle,ER_WS_ATTR_NAME,"Test1");
			
			ExcelRpt_WriteData (Sheethandle, "A1:D1", ExRConst_dataString, 1, 4, channelHeaders);
			
			
			ExcelRpt_WriteData (Sheethandle, "A2:A2001", ExRConst_dataDouble, SIZE, 1, time);
			ExcelRpt_WriteData (Sheethandle, "B2:B2001", ExRConst_dataDouble, SIZE, 1, data);
			ExcelRpt_WriteData (Sheethandle, "C2:C2001", ExRConst_dataDouble, SIZE, 1, UpLimit);
			ExcelRpt_WriteData (Sheethandle, "D2:D2001", ExRConst_dataDouble, SIZE, 1, LowLimit);
			
			ExcelRpt_WorkbookClose (excelworkbook, 1);
			
			ExcelRpt_ApplicationQuit (excelapphandle);

			CA_DiscardObjHandle(Sheethandle);
			CA_DiscardObjHandle(excelworkbook);			
			CA_DiscardObjHandle(excelapphandle);
}


void LoadXLSX(double*timeT,double*dataT,double*UpLimitT,double*LowLimitT)
{
	
	static CAObjHandle excelapphandle;
	static CAObjHandle excelworkbooktable;
	static CAObjHandle excelsheet;
	ExcelRpt_ApplicationNew(VTRUE,&excelapphandle);
			
	ExcelRpt_WorkbookOpen (excelapphandle, "Book1.xlsx", &excelworkbooktable);
	ExcelRpt_GetWorksheetFromName (excelworkbooktable, "Test1", &excelsheet);
	
	ExcelRpt_ReadData (excelsheet, "A2:A2001", ExRConst_dataDouble, timeT);
	ExcelRpt_ReadData (excelsheet, "B2:B2001", ExRConst_dataDouble, dataT);
	ExcelRpt_ReadData (excelsheet, "C2:C2001", ExRConst_dataDouble, UpLimitT);
	ExcelRpt_ReadData (excelsheet, "D2:D2001", ExRConst_dataDouble, LowLimitT);
	
	ExcelRpt_WorkbookClose (excelworkbooktable, 0);
	ExcelRpt_ApplicationQuit (excelapphandle);
	

	CA_DiscardObjHandle(excelsheet);
	CA_DiscardObjHandle(excelworkbooktable);			
	CA_DiscardObjHandle(excelapphandle);	
}







