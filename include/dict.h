//The Plugin of Dictionary module
#include "base.h"

#ifdef _WIN32
#include <windows.h>		//Use the api to change the color
#define OTHER_OS
#endif // _WIN32


#ifdef _WIN32
void Colorfy(unsigned char *StrCom);
#endif
void FindDict(FILE *DictFile, char CheckWord[], short* WordCount, struct EnWord Word[]);
bool InitDictOK(char FirstWord,FILE* *DictFile,short* WordCount,struct EnWord Word[]);

void NewLine();
