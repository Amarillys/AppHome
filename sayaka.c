/*
.
#
b 百度
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

char shortcut[255][20];
char address[255][255];

int main(int argc, char*argv[])
{
    _init();
    _run();
    return 0;
}



int _run()
{
	short get;
    char appname[20];
    while(1)
    {
		get=0;
    	printf("\nApp:");
        scanf("%s",appname);
        char tmp[255];
		if(appname[0]=='b')
		{
			memset(tmp,0,255);
			for(i=0;i<sizeof(appname);i++)
				appname[i]=appname[i+1];
			strcat(tmp,"start http://www.baidu.com/s?wd=");
			strcat(tmp,appname);
            system(tmp);
			get=1;
		}
		
        for(i=0;i<appcount;i++)
            if(strcmp(appname,shortcut[i])==0)
            {
				memset(tmp,0,255);
				strcat(tmp,"start ");
				strcat(tmp,address[i]);
            	system(tmp);
				get=1;
                break;
            }
			
		if(appname[0]=='#')
			_add();
			
		if(appname[0]=='.')
		{
			for(i=0;i<sizeof(appname);i++)
				appname[i]=appname[i+1];
		    system(appname);
			get=1;
		}
		
		if(appname[0]=='-')
		{
			memset(tmp,0,255);
			for(i=0;i<sizeof(appname);i++)
				appname[i]=appname[i+1];
			system("http://300report.jumpw.com/list.html?name="+appname);
			get=1;
		}
		
		if(get==0)
		{
			memset(tmp,0,255);
			strcat(tmp,"start ");
			strcat(tmp,appname);
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
        scanf("%s",address[appcount+1]);
		printf("    Name :");
        scanf("%s",shortcut[appcount+1]);
        fprintf(fp,"%s\n",shortcut[appcount+1]);
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
        fscanf(fp,"%s",shortcut[i]);
        fscanf(fp,"%s",address[i]);
        appcount++;
    }
}

