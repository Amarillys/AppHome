/*这是一个超级简单傻瓜的快捷启动程式
0是进入运行模式
1添加应用模式
举个栗子，输入 1 然后再拉个c:\windows\explorer.exe进入，然后回车，输入为1，下次按0再输入1就能运行这个exe了 */


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
        for(i=0;i<appcount;i++)
            if(strcmp(appname,shortcut[i])==0)
            {
            	system(address[i]);
				get=1;
                break;
            }
		if(get==0)
			_add();
	}
}

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