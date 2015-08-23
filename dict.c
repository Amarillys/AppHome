#define _CRT_SECURE_NO_WARNINGS
#include "dict.h"

bool InitDictOK(char FirstWord, FILE** DictFile, short* WordCount, struct EnWord Word[])   //Get and Save the Word and the Comment
{
	short  i = 0;
	char DictPath[20] = { "z:/English/" };
	char Comment[12801];

	strncat(DictPath, &FirstWord, 1);
	strcat(DictPath, ".txt");
	*DictFile = fopen(DictPath, "r");

	if (*DictFile == NULL){
		printf("Failed to find the dictionary!Please have a Check.");
		return false;
	}

	while (!feof(*DictFile)){
		fgets(Word[i].Word, 31, *DictFile);			//read the word
		Word[i].Word[strlen(Word[i].Word) - 1] = '\0';
		Word[i].Offset = ftell(*DictFile);			//read the offset of the comment
		fgets(Comment, 12800, *DictFile);		//just for skip the comment
		i++;
	}
	*WordCount = i;
	return true;
}

void FindDict(FILE *DictFile, char CheckWord[], short* WordCount, struct EnWord Word[])   //Search the Word and Print the Comment
{
	short i;
	char Comment[12801];
	for (i = 0; i < *WordCount; i++)
		if (strcmp(CheckWord, Word[i].Word) == 0){
			fseek(DictFile, Word[i].Offset, SEEK_SET);
			fgets(Comment, 12800, DictFile);
			printf("---->%s\n\n", Word[i].Word);
			Colorfy(Comment);
			return;
		}
	printf("									  --->No Results!QAQ");
}

void Colorfy(unsigned char *StrCom) //词典排版
{
	unsigned int i = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (StrCom[0] == '/')   //音标
	{
		putchar('/');
		i++;
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		while (StrCom[i] != '/')
		{
			putchar(StrCom[i]);
			i++;
		}
		putchar('/');
		i++;
	}

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	for (; i <= strlen(StrCom); i++)
	{
		if (StrCom[i] > 48 && StrCom[i] < 58)   //数字序号
		{
			NewLine();
			putchar(StrCom[i]);
			putchar(' ');
			i++;
			if (StrCom[i] == '.')
				putchar('.');
		}
		else if (StrCom[i] > 128)	//中文解释
		{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			putchar(StrCom[i]);
			i++;
			putchar(StrCom[i]);
			i++;
			while ((StrCom[i] != '.') && (StrCom[i] != ':') && (StrCom[i] != ')')){
				putchar(StrCom[i]);
				i++;
			}
			putchar(StrCom[i]);
			if (StrCom[i] == '.')
				NewLine();
		}
		//else if( StrCom[i] == '.')
		//NewLine();
		else{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			putchar(StrCom[i]);
		}
	}
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void NewLine(){
	putchar('\n');
}
