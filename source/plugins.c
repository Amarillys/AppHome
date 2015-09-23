#include "../include/plugins.h"

void AddPlugins(char Plugins[]){
    Plugins[0] = '.';
	Plugins[1] = '*';
}

bool DetectPlugins(char FirstChar,char Plugins[]){
    unsigned int i;
    for(i = 0;i < strlen(Plugins);i++)
		if (FirstChar == Plugins[i]){
			EnterPlugins(FirstChar);
			return true;
		}
    return false;
}

void DoNothing(){
	//What the fuck
}

void EnterPlugins(char FuncChar){
	switch (FuncChar){
	case '.':
		printf("Command : ");
		char InputCmd[32];
		fgets(InputCmd,32,stdin);
		InputCmd[strlen(InputCmd) - 1] = 0;
		system(InputCmd);
		break;

	case '*':
		printf("     ->PluginMode\n     b:baidu   d:EnDict   x:DecToHex :  ");
		char func;
		func = _getch();
		switch (func)	{
		case 'b':			//baidu search
			BaiduSearch();
			break;
		case 'd':			//dictionary
			LookOnDict();
			break;
		case 'x':			//convert to hex
			ConvertToHex();
			break;
		default:
			break;
		}

	default:
		break;
    }
}

void ConvertToHex(){
	printf("  To Convert :");
	int d;
	fflush(stdin);
	scanf("%d", &d);
	printf("										  ----> %X", d);
}

void BaiduSearch(){
	char tmpstr[192],tmp[255];
	printf(" Baidu Search :");
	gets(tmpstr);
	memset(tmp, 0, 255);
	strcat(tmp, "start http://www.baidu.com/s?wd=");
	strcat(tmp, tmpstr);
	system(tmp);
}

void LookOnDict(){
	struct EnWord Word[5671];
	FILE *Dict;
	Dict = NULL;
	short WordCount;
	char CheckWord[32];
	printf("Word To Check :");
	fflush(stdin);
	gets(CheckWord);

	if (!InitDictOK(CheckWord[0], &Dict, &WordCount, Word)){
		return;
		fclose(Dict);
	}
	FindDict(Dict, CheckWord, &WordCount, Word);
	fclose(Dict);
}

