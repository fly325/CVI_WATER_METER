#include <cviauto.h>
#include "excelreport.h"
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include <cvirte.h>		
#include <userint.h>
#include "project.h"
#include <DLLProject.h>

#define SIZE 2000
#define BUFFER_SIZE 10
#define PUMP_ON 	'F'
#define PUMP_STOP	'S'

static int panelHandle,ConnectHandle,GLHandle,GraphTabHandle,LogTabHandle,MGHandle,ID1 = 0,Time_Thread_handle=0,DGraphTabHandle,TableTabHandle; 
int err=0,com,baud,min_tr,max_tr,MtCtrl =1 ,HoldGraph=0;

//struct datastr
//{
//	int data[SIZE];
//	int time[SIZE];
//	int UpLimit[SIZE];
//	int LowLimit[SIZE];
//	int cnt;
//};
struct datastr Dataplot,ImportDataPlot;

//--------FUNCTIONS PROTOTYPES
int SaveTextToFile();
void ImportFileToText();
void UpdateLog(int data, unsigned char cmd);
int CVICALLBACK Time_Thread (void *Data);



//---------TIME VARIABLES-------------//
unsigned int year, month, day, hour, min, sec, weekDay;
char Date_string[512];
CVIAbsoluteTime absTime;
static const char * DaysOfWeek[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

time_t start_sec,elap_time;
//------------------------------------//


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "project.uir", PANEL)) < 0)
		return -1;
	if ((ConnectHandle = LoadPanel (0, "project.uir", PANEL_CONN)) < 0)
		return -1;
	if ((GLHandle = LoadPanel (0, "project.uir", PANEL_GRAP)) < 0)
		return -1;
	if ((MGHandle = LoadPanel (0, "project.uir", PANEL_MGT)) < 0)
		return -1;
	
	DisplayPanel (panelHandle);
	GetPanelHandleFromTabPage (GLHandle, PANEL_GRAP_TAB, 0, &GraphTabHandle);
	GetPanelHandleFromTabPage (GLHandle, PANEL_GRAP_TAB, 1, &LogTabHandle);
	GetPanelHandleFromTabPage (MGHandle, PANEL_MGT_TAB, 0, &DGraphTabHandle);
	GetPanelHandleFromTabPage (MGHandle, PANEL_MGT_TAB, 1, &TableTabHandle);
	CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE,Time_Thread,NULL, &Time_Thread_handle); // Always Update Time 
	ImportFileToText();
	RunUserInterface ();
	SaveTextToFile(0);
	DiscardPanel (panelHandle);
	DiscardPanel (ConnectHandle);
	DiscardPanel (GLHandle);
	DiscardPanel (MGHandle);
	
	return 0;
}

//---------FUNCTIONS 
void ImportFileToText()
{
	 char lineBuffer[512];  // Buffer to store each line (adjust size if needed)

    // Open the file for reading
    FILE *file = fopen ("c:\\Users\\edenm\\Afeka College Of Engineering\\CVI 2 - General\\Homework\\project\\log.txt", "r");
    if (file != NULL)
    {
        DeleteTextBoxLines(LogTabHandle, TABPANEL_2_TEXTBOX, 0, -1);
		
        while (fgets(lineBuffer, sizeof(lineBuffer), file) != NULL)
        {
           
            size_t len = strlen(lineBuffer);
            if (len > 0 && lineBuffer[len - 1] == '\n')
            {
                lineBuffer[len - 1] = '\0';
            }

            
            InsertTextBoxLine(LogTabHandle, TABPANEL_2_TEXTBOX, -1, lineBuffer);
        }

        
        fclose(file);
    }
    else
    {
        MessagePopup("Error", "No previous log file found or failed to open the file.");
    }
}
int SaveTextToFile(int saveflag)
{
	int lines;
	FILE *file ;
	GetNumTextBoxLines (LogTabHandle,TABPANEL_2_TEXTBOX , &lines);

    char textbuf[500];
	
	if (!saveflag) file = fopen ("c:\\Users\\edenm\\Afeka College Of Engineering\\CVI 2 - General\\Homework\\project\\log.txt", "w");
	else
	{
		char pathname[MAX_PATHNAME_LEN];
		if(FileSelectPopup ("C:\\Users\\edenm\\Afeka College Of Engineering\\CVI 2 - General\\Homework\\project", "LOG_Save.txt", "*.txt", "LOG File Save", VAL_SAVE_BUTTON, 0, 1, 1, 1,pathname ) == 0 )return(0);
		file = fopen (pathname, "w");
	}
	if (file != NULL)
    {
		for (int l = 0 ;l<lines ;l++)
		{
			
			GetTextBoxLine (LogTabHandle,TABPANEL_2_TEXTBOX , l,textbuf );
			fprintf(file, "%s\n", textbuf);
			
			
		}
		fprintf(file, "%s", "---------------------------------------------------------\n\n");
		if (saveflag)UpdateLog(0,'A');
		fclose(file);  
		
	}
     else
    {
        MessagePopup("Error", "Failed to save Log.");
    }

 	return(0);

}

int SaveDataToFile()
{
	FILE *file ;
	char pathname[MAX_PATHNAME_LEN];
	if (FileSelectPopup ("C:\\Users\\edenm\\Afeka College Of Engineering\\CVI 2 - General\\Homework\\project", "DATA_Save.txt", "*.txt", "LOG File Save", VAL_SAVE_BUTTON, 0, 1, 1, 1,pathname )==0)return(1);
	file = fopen (pathname, "w");
	if (file != NULL)
	{
		for (int l = 0 ;l<Dataplot.cnt ;l++)
		{
			fprintf(file, "%d %d %d %d\n", Dataplot.time[l],Dataplot.data[l],Dataplot.UpLimit[l],Dataplot.LowLimit[l]);	
		}
		fclose(file);
		UpdateLog(0,'B');
		
	}
	 else
    {
        MessagePopup("Error", "Failed to save Data.");
    }
	return (0);
}

int ImportDataFromSavedFile()
{	
	ImportDataPlot.cnt=0;
	FILE *file ;
	char pathname[MAX_PATHNAME_LEN];
	if (FileSelectPopup ("C:\\Users\\edenm\\Afeka College Of Engineering\\CVI 2 - General\\Homework\\project","DATA_Save.txt", "*.txt", "LOG File Select", VAL_OK_BUTTON, 0, 1, 1, 1, pathname)==0)return(1);
	file = fopen (pathname, "r");
	
	while (fscanf(file, "%d %d %d %d", &ImportDataPlot.time[ImportDataPlot.cnt], &ImportDataPlot.data[ImportDataPlot.cnt], &ImportDataPlot.UpLimit[ImportDataPlot.cnt], &ImportDataPlot.LowLimit[ImportDataPlot.cnt]) == 4)
 	{
        ImportDataPlot.cnt++;
        if (ImportDataPlot.cnt == SIZE) break;
    }

	fclose(file);
	return(0);
}

void UpdateLog(int data, unsigned char cmd)
{
	char stringPrint[500];
	UpdateLogDLL(data,cmd,stringPrint,Date_string); 
	SetCtrlVal (LogTabHandle, TABPANEL_2_TEXTBOX, stringPrint);
}


void DataPlotting(int seconds,int val)
{
	Dataplot.data[Dataplot.cnt]=val;
	Dataplot.time[Dataplot.cnt]=seconds;
	Dataplot.UpLimit[Dataplot.cnt]= max_tr;
	Dataplot.LowLimit[Dataplot.cnt]= min_tr;
	
	if (!HoldGraph)DeleteGraphPlot(GraphTabHandle,TABPANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);

	if (!HoldGraph)PlotXY (GraphTabHandle, TABPANEL_GRAPH, Dataplot.time, Dataplot.data, Dataplot.cnt+1, VAL_INTEGER, VAL_INTEGER, VAL_CONNECTED_POINTS, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_DK_BLUE);
	if (!HoldGraph)PlotXY (GraphTabHandle, TABPANEL_GRAPH, Dataplot.time,Dataplot.UpLimit, Dataplot.cnt+1, VAL_INTEGER, VAL_INTEGER, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_DASH, 1, VAL_GREEN);
	if (!HoldGraph)PlotXY (GraphTabHandle, TABPANEL_GRAPH, Dataplot.time,Dataplot.LowLimit, Dataplot.cnt+1, VAL_INTEGER, VAL_INTEGER, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_DASH, 1, VAL_RED);
	
	
	Dataplot.cnt++;
}


//---------------THREADS FUNCS
int CVICALLBACK Time_Thread (void *Data)
{
	while(1)
	{
	GetCurrentCVIAbsoluteTime(&absTime);
	CVIAbsoluteTimeToLocalCalendar(absTime, &year, &month, &day, &hour, &min, &sec, 0, &weekDay);
	sprintf(Date_string, "%02d:%02d:%02d  %s %02d/%02d/%04d", hour, min, sec, DaysOfWeek[weekDay], day, month, year);
	Delay(0.5);
	}
}

int CVICALLBACK SerDataFunc (void *Data)
{
	int cnt,num=0,flag=1;
	Dataplot.cnt=0;
	char data[BUFFER_SIZE];
	int stoploop = *(int *)Data;
	time(&start_sec);
	while (stoploop) 
	{
	stoploop = *(int *)Data;
	cnt = ComRdTerm (com, data, sizeof(data)-1,'\n');
			if (cnt>0) //There is data in the buffer 
			{
				data[cnt-1] = '\0';
				num = atoi(data);
				if (num<0||num>400)continue; // ignore all the unwanted data or errors from the first measurement
				num = (400 - num);
			}
			
			SetCtrlVal(panelHandle,PANEL_WATERTANK,num);
			
			int diff =(int) difftime(time(&elap_time),start_sec);
			DataPlotting(diff,num);


			
			if(num < min_tr&& flag == 1)
			{
				Delay(0.1);
				sendAlert(PUMP_ON,com); 
				SetCtrlVal(panelHandle,PANEL_PUMP_ON,1);
				flag = 0 ;
				UpdateLog(num,PUMP_ON); // PUMP ON
			}
			if(num > max_tr&& flag == 0 )
			{
				Delay(0.1);
				sendAlert(PUMP_STOP,com); 
				SetCtrlVal(panelHandle,PANEL_PUMP_ON,0);
				flag =1;
				UpdateLog(num,PUMP_STOP); // PUMP STOP  
				
			}
			
	}
	return(0);
}



//------------------BUTTONS
void CVICALLBACK G_and_L (int menuBar, int menuItem, void *callbackData,
						  int panel)
{
	DisplayPanel (GLHandle);
}
int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

void CVICALLBACK connect_menu (int menuBar, int menuItem, void *callbackData,
							   int panel)
{
	DisplayPanel (ConnectHandle);
}

int CVICALLBACK Disconnect (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			MtCtrl = 0;
			CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE,ID1, OPT_TP_PROCESS_EVENTS_WHILE_WAITING);
			CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, ID1);
			UpdateLog(0,'D');
			SetCtrlVal(panelHandle,PANEL_WATERTANK,0);
			SetCtrlVal(panelHandle,PANEL_COMLED,0);
			SetCtrlAttribute (panelHandle, PANEL_DISCONNECT, ATTR_DIMMED, 1);
			break;
	}
	return 0;
}

int CVICALLBACK Close (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (ConnectHandle);
			break;
	}
	return 0;
}


int CVICALLBACK Close_Gr (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (GLHandle);
			break;
	}
	return 0;
}

//-----------------------------
int CVICALLBACK connect (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal(ConnectHandle,PANEL_CONN_COM,&com);
			GetCtrlVal(ConnectHandle,PANEL_CONN_BAUD,&baud);
			if (OpenComConfig (com, "", baud, 0, 8, 1, 512, 512)>=0) // Success
			{
				SetCtrlVal(panelHandle,PANEL_COMLED,1);
				MtCtrl = 1;
				CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, SerDataFunc, &MtCtrl, &ID1);
				GetCtrlVal(panelHandle,PANEL_UP_THRES,&max_tr);
				GetCtrlVal(panelHandle,PANEL_LOW_THRES,&min_tr);
				UpdateLog(com,'C');
				SetCtrlAttribute (panelHandle, PANEL_DISCONNECT, ATTR_DIMMED, 0);
				HidePanel(ConnectHandle);
			}
			else
			{
				MessagePopup ("Connection Error", "Failed to Connect");
				return(0);
			}
			

			break;
	}
	return 0;
}







int CVICALLBACK Up_Thres (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(panelHandle,PANEL_UP_THRES,&max_tr);
			if (min_tr>= max_tr )
			{
				SetCtrlVal(panelHandle,PANEL_LOW_THRES,max_tr-1);
				min_tr =max_tr-1;
			}
			UpdateLog(max_tr,'U');
				

			break;
	}
	return 0;
}

int CVICALLBACK Low_Thres (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(panelHandle,PANEL_LOW_THRES,&min_tr);
			if (max_tr<= min_tr )
			{
				SetCtrlVal(panelHandle,PANEL_UP_THRES,min_tr+1);
				max_tr=min_tr+1;
			}
			UpdateLog(min_tr,'L');
			break;
	}
	return 0;
}

int CVICALLBACK Clear_log (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		 const char *filename = "log.txt";  

	    
	    if (remove(filename) == 0) 
		{
	      	DeleteTextBoxLines(LogTabHandle, TABPANEL_2_TEXTBOX, 0, -1);
			 MessagePopup("Success", "LOG Deleted Successfully.");
	    } else {
	        MessagePopup("Error", "Error Deleting LOG."); 
	    }

				break;
		}
		return 0;
}

int CVICALLBACK Clear_gr (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot(GraphTabHandle,TABPANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			Dataplot.cnt = 0;
			memset(Dataplot.data, 0, SIZE);
			memset(Dataplot.LowLimit, 0, SIZE);
			memset(Dataplot.UpLimit, 0, SIZE);
			memset(Dataplot.time, 0, SIZE);
			time(&start_sec);
			

			break;
	}
	return 0;
}

int CVICALLBACK cursorGR (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	double X,Y;
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetGraphCursor (GraphTabHandle, TABPANEL_GRAPH, 1, &X,&Y );
			SetCtrlVal(GraphTabHandle,TABPANEL_WL,Y);
			SetCtrlVal(GraphTabHandle,TABPANEL_WL_2,X);
			break;
	}
	return 0;
}

int CVICALLBACK Hold (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(GraphTabHandle,TABPANEL_HOLD,&HoldGraph);

			break;
	}
	return 0;
}


int CVICALLBACK CloseDM (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (MGHandle);

			break;
	}
	return 0;
}

void CVICALLBACK Open_DM (int menuBar, int menuItem, void *callbackData,
						  int panel)
{
	
	DisplayPanel (MGHandle);
}

int CVICALLBACK Log_St (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			SaveTextToFile(1);		
			break;
	}
	return 0;
}

int CVICALLBACK Save_data_file (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 SaveDataToFile();
			
			break;
	}
	return 0;
}

int CVICALLBACK Import_Data (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		if (ImportDataFromSavedFile()==1)break;
		
		DeleteGraphPlot(DGraphTabHandle,TABPANEL_3_GRAPH, -1, VAL_IMMEDIATE_DRAW);

		PlotXY (DGraphTabHandle, TABPANEL_3_GRAPH, ImportDataPlot.time, ImportDataPlot.data, ImportDataPlot.cnt, VAL_INTEGER, VAL_INTEGER, VAL_CONNECTED_POINTS, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_DK_BLUE);
		PlotXY(DGraphTabHandle, TABPANEL_3_GRAPH, ImportDataPlot.time,ImportDataPlot.UpLimit, ImportDataPlot.cnt, VAL_INTEGER, VAL_INTEGER, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_DASH, 1, VAL_GREEN);
		PlotXY (DGraphTabHandle, TABPANEL_3_GRAPH, ImportDataPlot.time,ImportDataPlot.LowLimit, ImportDataPlot.cnt, VAL_INTEGER, VAL_INTEGER, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_DASH, 1, VAL_RED);
		
		break;
	}
	return 0;
}

int CVICALLBACK cursorGR2 (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	double X,Y;
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetGraphCursor (DGraphTabHandle, TABPANEL_3_GRAPH, 1, &X,&Y );
			SetCtrlVal(DGraphTabHandle,TABPANEL_3_WL,Y);
			SetCtrlVal(DGraphTabHandle,TABPANEL_3_WL_2,X);
			break;
	}
	return 0;
}

int CVICALLBACK clr (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot(DGraphTabHandle,TABPANEL_3_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			break;
	}
	return 0;
}

void CVICALLBACK About (int menuBar, int menuItem, void *callbackData,
						int panel)
{
	MessagePopup ("WATER TOWER CONTROL SYSTEM", "                            Eden MAMAN \n\n                          © October 2024");

}

int CVICALLBACK Save_data_CSV (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
			
		case EVENT_COMMIT:
		SaveXLSX(Dataplot);
			break;
	}
	return 0;
}


int CVICALLBACK Imp_Excel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	char* channelHeaders[] = {"Time","Water Level","UP Limit","Low Limit"};
	double timeT[SIZE],dataT[SIZE],UpLimitT[SIZE],LowLimitT[SIZE];
	int loadflag = 0 ;

	switch (event)
	{
		case EVENT_COMMIT:
			LoadXLSX(timeT,dataT,UpLimitT,LowLimitT);
			if (loadflag == 0)
			{
				InsertTableColumns (TableTabHandle, TABPANEL_4_TABLE, -1, 4, VAL_CELL_NUMERIC);
				InsertTableRows (TableTabHandle, TABPANEL_4_TABLE, -1, 1, VAL_CELL_STRING);
				InsertTableRows (TableTabHandle, TABPANEL_4_TABLE, -1, SIZE, VAL_CELL_NUMERIC);
				loadflag = 1;
			}
			
			SetTableCellRangeVals (TableTabHandle, TABPANEL_4_TABLE, MakeRect(1,1,1,4), channelHeaders, VAL_ROW_MAJOR);
			SetTableCellRangeVals (TableTabHandle, TABPANEL_4_TABLE,MakeRect(2,1,SIZE,1), timeT, VAL_COLUMN_MAJOR);
			SetTableCellRangeVals (TableTabHandle, TABPANEL_4_TABLE,MakeRect(2,2,SIZE,1), dataT, VAL_COLUMN_MAJOR);
			SetTableCellRangeVals (TableTabHandle, TABPANEL_4_TABLE,MakeRect(2,3,SIZE,1), UpLimitT, VAL_COLUMN_MAJOR);
			SetTableCellRangeVals (TableTabHandle, TABPANEL_4_TABLE,MakeRect(2,4,SIZE,1), LowLimitT, VAL_COLUMN_MAJOR);
			

			break;
	}
	return 0;
}


int CVICALLBACK Table_Clear (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteTableRows (TableTabHandle, TABPANEL_4_TABLE, 1, -1);


			break;
	}
	return 0;
}
