#define _CRT_SECURE_NO_WARNINGS
#include "../include/dict.h"

bool InitDictOK(char FirstWord, FILE** DictFile, short* WordCount, struct EnWord Word[])   //Get and Save the Word and the Comment
{
	short  i = 0;
	char DictPath[20] = { "English/" };
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
			#ifdef _WIN32
			Colorfy(Comment);
			#endif // _WIN32
			return;
		}
	printf("									  --->No Results!QAQ");
}

#ifdef _WIN32
void Colorfy(unsigned char *StrCom) //¥ µ‰≈≈∞Ê
{
	unsigned int i = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (StrCom[0] == '/')   //“Ù±Í
	{
		putchar('/');
		i++;
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		while (StrCom[i] != '/'){
			putchar(StrCom[i]);
			i++;
		}
		putchar('/');
		i++;
	}

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	for (; i <= strlen(StrCom); i++)
	{
		if (StrCom[i] > 48 && StrCom[i] < 58)   // ˝◊÷–Ú∫≈
		{
			NewLine();
			putchar(StrCom[i]);
			putchar(' ');
			i++;
			if (StrCom[i] == '.')
				putchar('.');
		}
		else if (StrCom[i] > 128)	//÷–ŒƒΩ‚ Õ
		{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			putchar(StrCom[i++]);
			putchar(StrCom[i++]);
			while ((StrCom[i] != '.') && (StrCom[i] != ':') && (StrCom[i] != ')')){
				putchar(StrCom[i]);
				i++;
			}
			putchar(StrCom[i]);
			if (StrCom[i] == '.')
				NewLine();
		}else{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			putchar(StrCom[i]);
		}
	}
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
}
#endif // _WIN32
void NewLine(){
	putchar('\n');
}
