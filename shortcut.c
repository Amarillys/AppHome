#define _CRT_SECURE_NO_WARNINGS
#include "shortcut.h"

void AddShortCut(struct App ShortCut[],short *appcount){
    int a;
	a = 1;
	FILE *fp;
	while(a){
		fflush(stdin);
		fp=fopen("app.dat","a");
		printf("\n Add Mode:\n	Path:");            //get the shortcut inputted
		gets(ShortCut[++(*appcount)].Path);
		printf("	Name :");
		scanf("%s",ShortCut[(*appcount)].Name);
		fprintf(fp,"%s\n",ShortCut[(*appcount)].Name);          //write into app.dat
		fprintf(fp,"%s\n",ShortCut[(*appcount)].Path);
		printf("QAQ:");
		scanf("%d",&a);     //again?
	}
	fflush(stdin);
	fclose(fp);
}

void AntiFill(short length){
	short i;
	for (i = 0; i < length; i++)
		putchar(0);
	for (i = 0; i < length; i++)
		putchar('\b');
}

short AutoFill(int length, char EntireStr[]){
	short i,count;
	i = length;
	count = (int)strlen(EntireStr) - i;
	for (; i < count + length; i++)
		putchar(EntireStr[i]);
	for (i = length; i < count + length; i++)
		putchar('\b');
	return count;		//return the number of the char that have been auto filled.
}

void LoadShortCut(struct App ShortCut[],short *appcount){
	FILE *fp;
	if ((fp = fopen("app.dat", "r")) == NULL){
		printf("  !:Cannot find app.dat , now create new one.\n");
		fp = fopen("app.dat", "w");
	}
	short i,count;
	fclose(fp);
	fp = fopen("app.dat", "r");

	for (i = 0, count = 0; !(feof(fp)); i++)
	{
		fscanf(fp, "%s", ShortCut[i].Name);
		fscanf(fp, "%s", ShortCut[i].Path);
		count++;
	}
	*appcount = count;
	fclose(fp);
}

bool DetectChar(char InputChar[], short *ResultIndex, struct App ShortCut[], short *appcount){
	uint8 length;
	short i;
	length = strlen(InputChar);
	for (i = 0; i < *appcount; i++){
		char tmpstr[32] = { 0 };
		strncat(tmpstr, ShortCut[i].Name, length);
		if (strcmp(tmpstr, InputChar) == 0){
			*ResultIndex = i;
			return true;
		}
	}
	return false;
}
