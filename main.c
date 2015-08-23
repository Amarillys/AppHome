#define _CRT_SECURE_NO_WARNINGS

#include "base.h"
#include "plugins.h"
#include "shortcut.h"
#include "Version.h"

struct App ShortCut[512];	//store the ShortCut
short appcount;
short FillCount;
short ResultIndex;
bool IsDetected;
bool IsFirst, IsPlugins;   //for the judge if define other function[in plugins]
char InputChar[32];     //to save the char  inputted
char RunPath[255];
char Plugins[32] = { 0 };
uint8 ICount;
void DelCurrentChar();
void Init();

int main(void)
{
    printf("******************************************\n   Welcome to Amarillys's World V1.000\n******************************************");
    AddPlugins(Plugins);			//load the plugin keys
	LoadShortCut(ShortCut, &appcount);			//load shortcuts from app.dat

	while (1){			//always running
        Init();			//Initialize
        while(((InputChar[ICount] = _getch())!= '\r') && !IsPlugins){				//If the input char is 'Enter' or it has enter the function of plugins,A loop finish.

			if (IsFirst){			//Remain this modules to judge if user enter the plugin keyword.
				if (InputChar[0] == '\b' || DetectPlugins(InputChar[0], Plugins)){			//deal with the backspace,regard it as a plugins key and Detect  plugins and run if is.
					IsPlugins = true;			//turn on the switch to exit the loop
					break;
				}else if(InputChar[0] == '#')
					AddShortCut(ShortCut, &appcount);
					IsPlugins = true;			//turn on the switch to exit the loop
					break;
			}

			if (!IsPlugins){			//Continue to receive the string
				if (InputChar[ICount] == '\b'){			//deal with the backspace,but it cannot be regard as a plugin when it isn't the first input
					AntiFill(FillCount);			//del the filled char
					DelCurrentChar();
					InputChar[ICount] = 0;
					ICount--;
				}
				else{
					putchar(InputChar[ICount]);			//Display the inputchar
					if ((IsDetected = DetectChar(InputChar, &ResultIndex, ShortCut, &appcount)) == true)			//Detect the inputstring and get the result.
						FillCount = AutoFill(strlen(InputChar), ShortCut[ResultIndex].Name);
					else
						AntiFill(FillCount);			//del the filled char
					ICount++;			//For Next input
				}
			}else{
				IsPlugins = false;
				IsFirst = false;
				break;
			}
		}
		NewLine();
		//the input has finished
		if (!IsPlugins)
			if(IsDetected){
				strcat(RunPath, "start ");			//Merge the string to be ready to run
				strcat(RunPath, ShortCut[ResultIndex].Path);
				system(RunPath);
			}else
				system(InputChar);
	}
    return 0;
}

void DelCurrentChar(){
	putchar('\b');
	putchar(0);
	putchar('\b');
}

void Init(){
	memset(InputChar, 0, 15);
	memset(RunPath, 0, 255);
	FillCount = 0;
	IsDetected = false;
	IsFirst = true;
	IsPlugins = false;
	ICount = 0;
	printf("\n\n Maikaze Seikai ---->");
}
