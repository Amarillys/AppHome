#define _CRT_SECURE_NO_WARNINGS     //Ignore the warning of Visual Studio

#include "include/base.h"
#include "include/plugins.h"
#include "include/shortcut.h"
#include "include/Version.h"
#include <time.h>

struct App ShortCut[512];	        //store the ShortCuts
short appcount;         //to count the quanilty of the shortcuts
short FillCount;        //to save the number of the char that autofix
short ResultIndex;      //to save the result Index of the string matching if matching successfully
bool IsDetected;        //to save the result of the string matching
bool IsExited;        //to judge whether it is exit or start
char InputChar[32];     //to save the char  inputted
char RunPath[260];
char Plugins[32] = { 0 };
uint8 ICount;       //to save the number of the char inputted

time_t nowtime;
struct tm *timeinfo;
void GetTime();
void SaveTime();
void PrintTime();

void DelCurrentChar();      //custom function
void Init();        //Initilize

int main(void)
{
    printf("*********************************************\n     Welcome to Amarillys's World V1.002\n*********************************************");
    SaveTime();     //Save the time of starting
    atexit(SaveTime);       //for the summing times of running/using computer
    AddPlugins(Plugins);			//load the plugin keys
	LoadShortCut(ShortCut, &appcount);			//load shortcuts from app.dat

    CMDSTART:
	    Init();			//Initialize
	    while((InputChar[ICount] = _getch())!= '\r'){				//If the input char is 'Enter' or it has enter the function of plugins,A loop finish.
            if (InputChar[0] == '\b' || DetectPlugins(InputChar[0], Plugins))			//deal with the backspace,regard it as a plugins key and Detect  plugins and run if is.
				goto CMDSTART;
			else if(InputChar[0] == '#'){       //Add shortcut function
				AddShortCut(ShortCut, &appcount);
				goto CMDSTART;
			}
            if (InputChar[ICount] == '\b'){			//deal with the backspace,but it cannot be regard as a plugin when it isn't the first input
                AntiFill(FillCount);			//del the filled char
                DelCurrentChar();
                InputChar[ICount] = 0;
                ICount--;
            }else{
                putchar(InputChar[ICount]);			//Display the inputchar
                AntiFill(FillCount);			//del the filled char
                if ((IsDetected = DetectChar(InputChar, &ResultIndex, ShortCut, &appcount)) == true)			//Detect the inputstring and get the result.
                    FillCount = AutoFill(strlen(InputChar), ShortCut[ResultIndex].Name,true);
                else
                    AntiFill(FillCount);			//del the filled char
                ICount++;			//For Next input
            }
        }
        if(IsDetected){
            strcat(RunPath, "start ");			//Merge the string to be ready to run
            strcat(RunPath, ShortCut[ResultIndex].Path);
            system(RunPath);
            AutoFill(strlen(InputChar)-1,ShortCut[ResultIndex].Name,false);
        }else{
            strcat(RunPath, "start ");
            strcat(RunPath,InputChar);
            system(RunPath);
        }
        PrintTime();
        goto CMDSTART;
    return 0;
}

void DelCurrentChar(){      //custom function
	putchar('\b');
	putchar(0);
	putchar('\b');
}

void Init(){      //custom function
	memset(InputChar, 0, 15);
	memset(RunPath, 0, 255);
	FillCount = 0;
	IsDetected = false;
	ICount = 0;
	printf("\n\n Maikaze Seikai ----> ");
}

void GetTime(){
    time(&nowtime );
    timeinfo = localtime( &nowtime);
    timeinfo->tm_year = timeinfo->tm_year + 1900;
    timeinfo->tm_mon = timeinfo->tm_mon + 1;
}

void SaveTime(){
    GetTime();
    FILE *fp;
    fp = fopen("Timelog.dat","a");

    if(!IsExited){
        printf("\n****            Run : %02d:%02d:%02d           ****",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
        fprintf(fp,"\nStart : ");
        IsExited = true;
    }else{
        fprintf(fp,"\nEnd : ");
    }

    fprintf(fp,"%02d-%02d-%02d %02d:%02d:%02d,",
            timeinfo->tm_year , timeinfo->tm_mon ,timeinfo->tm_mday,
            timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
    fclose(fp);
}

void PrintTime(){
    GetTime();
    printf("   ||--->%02d:%02d:%02d",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
}
