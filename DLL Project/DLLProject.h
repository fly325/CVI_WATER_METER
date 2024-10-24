#define SIZE 2000


char* channelHeaders[] = {"Time","Water Level","UP Limit","Low Limit"};
struct datastr
{
	int data[SIZE];
	int time[SIZE];
	int UpLimit[SIZE];
	int LowLimit[SIZE];
	int cnt;
};


__declspec(dllexport)void sendAlert(char cmd,int com);
__declspec(dllexport)void SaveXLSX(struct datastr Data);
__declspec(dllexport)void LoadXLSX(double*timeT,double*dataT,double*UpLimitT,double*LowLimitT);
__declspec(dllexport)void UpdateLogDLL(int data,unsigned char cmd,char *stringPrint,char *Date_string);