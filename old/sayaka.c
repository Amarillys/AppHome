#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

int _run(void);
int _add(void);
int _del(void);
int _init(void);
int _detect(char *inputname,int ilen);
void InitDict(char FirstWord);
void FindDict(char *Word);
void Colorfy(unsigned char *StrCom);

inline void NewLine(){
		putchar('\r');
		putchar('\n');
}

FILE *fp;
short appcount;
short endi,firstdetect,firstinput;
short get;
short formerlen,tmpstrlen;
int lastselect[10];
int last,_last;

char existapp[255][20];
char address[255][255];
char copyapp[255][20];
char tmp[255];

//EnDictionary
FILE *DictFile;
FILE *LearnLog;
unsigned char Comment[12800];
char EnWord[5600][32];
int EnWordOffset[5600];
char CheckWord[32];
char FirstWord;
short WordCount;

int main(int argc, char*argv[])
{
	_last=last=9;
	memset(lastselect,0,10);
	_init();
	_run();
	return 0;
}

int _run()
{
	short _i,_select;
	char inputname[20];
	int backlen,j,upkey;
	while(1)
	{
		printf("\n App[ #-:add .->me b->baidu ] --->");
		memset(inputname,0,20);
		//endi=0;
		firstdetect = 1;
		firstinput = 1;
		formerlen = 0;

		for( _i=0;inputname[_i]=getch();_i++)
		{
			if(inputname[_i]=='\b' && get == 1)  //deal with the backspack key
			{
				inputname[_i]=0;
				inputname[_i-1]=0;
				backlen=formerlen;
				putchar('\b');
				while((formerlen--)>-1)
					putchar('\0');

				while((backlen--)>-1)
					putchar('\b');
				printf("%s",inputname);
				if(_i=1)
					firstinput=1;
				_i-=2;
				get=0;
				continue;
			}

			if(inputname[_i]=='\b' && get == 0)
			{	inputname[_i]=0;
				inputname[_i-1]=0;
				putchar('\b');
				putchar('\0');
				putchar('\b');
				_i-=2;
				continue;
				}

			if(inputname[_i]==-32)
				if((j=getch())==75)
				{
					putchar('\b');
					_i-=2;
					continue;
				}

			if(inputname[_i]==-32)
				if((j=getch())==77)
				{
					putchar(inputname[_i]);
					_i+=1;
					continue;
				}

			if(inputname[_i]==13)	//deal with the enter key
			{
				printf("\r\n");
				inputname[_i]='\0';
				firstdetect = 0;

				if(get==1)
				{
					memset(tmp,0,255);
					strcat(tmp,"start ");
  					strcat(tmp,address[_select]);
  					system(tmp);
					while((lastselect[_last]==_select) || (lastselect[_last]!=0))
						_last--;
					lastselect[_last] = _select ;
					get=1;
					//last--;
					break;
				}
				else
				{
					memset(tmp,0,255);
					strcat(tmp,"start ");
  					strcat(tmp,inputname);
  					system(tmp);
					get=1;
					break;
				}
			}

			if( firstinput == 1 )	//the first input key,which decide the function
			{
				if(inputname[0]=='#')
					_add();

				if(inputname[0]==-32)  //detect the key "up"
					if((j=getch())==72)
					{
						printf("%s",existapp[(lastselect[last])]);
						_select=lastselect[last];
						last--;
						for(j=0;j<strlen(existapp[(lastselect[last])]);j++)
							putchar('\b');
						get=1;

						upkey=1;
						_i=-1;
						inputname[0]=0;
						continue;
					}

				if(inputname[0]=='x')
				{
					inputname[0]='\0';
					printf("To Convert :");
					int d;
					fflush(stdin);
					scanf("%d",&d);
					printf("										  ----> %X",d);
					_run();
				}

				if(inputname[0] == '-')
				{
					inputname[0]='\0';
					printf("Word To Check :");
					fflush(stdin);
					gets(CheckWord);
					InitDict(CheckWord[0]);
					FindDict(CheckWord);
					_run();
				}

				if(inputname[0]=='b')
				{
					inputname[0]='\0';
					printf("Baidu Search :");
					gets(inputname);
					memset(tmp,0,255);
					strcat(tmp,"start http://www.baidu.com/s?wd=");
					strcat(tmp,inputname);
					system(tmp);
					_run();
				}

				if( inputname[0]=='.')
				{
					printf("Command :");
					inputname[0]='\0';
					gets(inputname);
					system(inputname);
					_run();
				}
				putchar(inputname[_i]);
				_select = _detect(inputname,_i);
  				firstinput = 0;
			}
	 		else
	  		{
				putchar(inputname[_i]);
 				_select = _detect(inputname,_i);
	   		}
		}
	}
}

int _detect(char *inputname,int ilen)
{
	short i,j;
	int k,l;
	get=0;l=0;
	char copyinput[20];
	memset(copyinput,0,20);
	strcat(copyinput,inputname);

	if( get == 0 )
	{
 		for(i=0;i<appcount-1;i++)
   		{
			memset(copyapp[i],0,20);
			strcat(copyapp[i],existapp[i]);
			copyapp[i][ilen+1]='\0';
		}

		for(i=0;i<appcount+1;i++)
			if(strcmp(copyinput,copyapp[i])==0)
			{
				for( j = 1,tmpstrlen = strlen( existapp[i] ) ; j < tmpstrlen - ilen ;j++)
					putchar(existapp[i][j+ilen]);

				k=formerlen-ilen;
				if(firstinput==1)
					k=tmpstrlen-ilen;

				while((formerlen--)-tmpstrlen>0)
					putchar('\0');

				for(l=1;l<k;l++)
					putchar('\b');
				get=1;
				formerlen = tmpstrlen;
				//system("pause");
		   		break;
			}
			else
				get=0;
	}

	if(get==0)   //other command in system
	{
		l=k=formerlen-ilen;
 		while((k--)>0)
			putchar('\0');

  		while(l-->0)
 			putchar('\b');

	}
	firstdetect = 0;
	firstinput = 0;
	return i;
}

int _add()
{
	int a;
	a = 1;
	while(a)
	{
		fflush(stdin);
		fp=fopen("app.dat","a");
		printf("\n Add Mode:\n	Path:");
		gets(address[appcount+1]);
		printf("	Name :");
		scanf("%s",existapp[appcount+1]);
		fprintf(fp,"%s\n",existapp[appcount+1]);
		fprintf(fp,"%s\n",address[appcount+1]);
		printf("QAQ:");
		scanf("%d",&a);
		appcount++;
	}
	fflush(stdin);
	fclose(fp);
	_init();
	_run();
}

int _del()
{
	printf("= =||");
	appcount--;
}

int _init()
{
	short i;
	if((fp=fopen("app.dat","r"))==NULL)
	{
		fp=fopen("app.dat","w");
		appcount=0;
	}
	fclose(fp);
	fp=fopen("app.dat","r");

	for(i=0,appcount=0;!(feof(fp));i++)
	{
		fscanf(fp,"%s",existapp[i]);
		fscanf(fp,"%s",address[i]);
		appcount++;
	}
	fclose(fp);
}

void InitDict(char FirstWord)   //Get and Save the Word and the Comment
{
	short ch,i = 0;
	char DictPath[20] = {"English/"};
	strncat(DictPath,&FirstWord,1);
	strcat(DictPath,".txt");
	DictFile = fopen(DictPath,"r");

	if(DictFile == NULL)
	{
		printf("Failed to find the dictionary!Please have a Check.\n");
		_run();
	}

	while(!feof(DictFile))
	{
		fgets(EnWord[i],32,DictFile);
		EnWord[i][strlen(EnWord[i])-1] = '\0';
		EnWordOffset[i] = ftell(DictFile);
		fgets(Comment,12800,DictFile);
		i++;
	}

	WordCount = i;
}

void FindDict(char *Word)   //Search the Word and Print the Comment
{
	int i;
	int log;

	for(i = 0;i < WordCount;i++)
		if(strcmp(Word,EnWord[i]) == 0)
		{
			fseek(DictFile,EnWordOffset[i],SEEK_SET);
			fgets(Comment,12800,DictFile);
			printf("---->%s\n\n",EnWord[i]);
			Colorfy(Comment);
			fclose(DictFile);
			printf("\n Add this word to the LearnLog? [y/n]->");
			scanf("%d",&log);
			if(log == 'y')
			{
				LearnLog = fopen("LearnLog.txt","a+");
				fprintf(LearnLog,"Word:%s\nComment:  %s\n",EnWord[i],Comment);
				fclose(LearnLog);
			}
			_run();
		}
	printf("									  --->No Results!QAQ");
	fclose(DictFile);
}

void Colorfy(unsigned char *StrCom) //词典排版
{
	int i = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if( StrCom[0] == '/')   //音标
	{
		putchar('/');
		i++;
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN);
		while(StrCom[i] !='/')
		{
			putchar(StrCom[i]);
			i++;
		}
		putchar('/');
		i++;
	}

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE| FOREGROUND_GREEN | FOREGROUND_RED);
	for( ;i <= strlen(StrCom);i++)
	{
		if( StrCom[i] > 48 && StrCom[i] < 58)   //数字序号
		{
			NewLine();
			putchar(StrCom[i]);
			putchar(' ');
			i++;
			if( StrCom[i] == '.')
				putchar('.');
		}
		else if( StrCom[i] > 128)	//中文解释
		{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY |  FOREGROUND_GREEN);
			putchar(StrCom[i]);
			i++;
			putchar(StrCom[i]);
			i++;
			while( (StrCom[i] != '.') && (StrCom[i] != ':') && (StrCom[i] != ')')){
				putchar(StrCom[i]);
				i++;
			}
			putchar(StrCom[i]);
			if( StrCom[i] == '.')
				NewLine();
		}
		//else if( StrCom[i] == '.')
			//NewLine();
		else{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE| FOREGROUND_GREEN | FOREGROUND_RED);
			putchar(StrCom[i]);
		}
	}
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE| FOREGROUND_GREEN );
}