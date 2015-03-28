/*
.
#
b ??
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _run(void);
int _add(void);
int _del(void);
int _init(void);

FILE *fp;
short i;
short appcount;

char existapp[255][20];
char address[255][255];

int main(int argc, char*argv[])
{
    _init();   //初始化
    _run();
    return 0;
}


int _run()
{
	short get;    //执行结果标志 
    char inputname[20];    //输入保存
    while(1)
    {
		get=0;
    	printf("\n App(#:add .:me b:baidu -:300 )  ):");
        gets(inputname);
        char tmp[255];
		if(inputname[0]=='b')
		{
			memset(tmp,0,255);
			for(i=0;i<strlen(inputname);i++)
				inputname[i]=inputname[i+1];
			strcat(tmp,"start http://www.baidu.com/s?wd=");
			strcat(tmp,inputname);
            system(tmp);
			get=1;
		}
		
        for(i=0;i<appcount;i++)
            if(strcmp(inputname,existapp[i])==0)
            {
				memset(tmp,0,255);
				strcat(tmp,"start ");
				strcat(tmp,address[i]);
            	system(tmp);
				get=1;
                break;
            }
			
		if(inputname[0]=='#')
			_add();
			
		if(inputname[0]=='.')
		{
			for(i=0;i<strlen(inputname);i++)
				inputname[i]=inputname[i+1];
		    system(inputname);
			get=1;
		}
		
		if(inputname[0]=='-')
		{
			memset(tmp,0,255);
			for(i=0;i<strlen(inputname);i++)
				inputname[i]=inputname[i+1];
			strcat(tmp,"start http://300report.jumpw.com/list.html?name=");
			strcat(tmp,inputname);
			system(tmp);
			get=1;
		}
		
		if(get==0)
		{
			memset(tmp,0,255);
			strcat(tmp,"start ");
			strcat(tmp,inputname);
			system(tmp);
		}
	}
}
//http://300report.jumpw.com/list.html?name=Amarillys
int _add()
{
    int a;
    while(a)
    {
		printf("\n Add Mode:\n    Path:");
        gets(address[appcount+1]);
		printf("    Name :");
        scanf("%s",existapp[appcount+1]);
        fprintf(fp,"%s\n",existapp[appcount+1]);
        fprintf(fp,"%s\n",address[appcount+1]);
        printf("QAQ");
        scanf("%d",&a);
        appcount++;
    }
    fclose(fp);
	_init();
	_run();
}

int _del()
{
    printf("\(?-?)/");
    appcount--;
}

int _init()
{
    if((fp=fopen("app.dat","r"))==NULL)
    {
        fp=fopen("app.dat","w");
        appcount=0;
    }
    fclose(fp);
    fp=fopen("app.dat","a+");

    for(i=0,appcount=0;!(feof(fp));i++)
    {
        fscanf(fp,"%s",existapp[i]);
        fscanf(fp,"%s",address[i]);
        appcount++;
    }
}

