//The Plugin of Dictionary module
#include <windows.h>		//Use the api to change the colo
#include "base.h"

void Colorfy(unsigned char *StrCom);
void FindDict(FILE *DictFile, char CheckWord[], short* WordCount, struct EnWord Word[]);
bool InitDictOK(char FirstWord,FILE* *DictFile,short* WordCount,struct EnWord Word[]);

void NewLine();