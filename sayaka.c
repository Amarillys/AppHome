#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int _run(void);
int _add(void);
int _del(void);
int _init(void);
int _detect(char *inputname,int ilen);

FILE *fp;
short appcount;
short endi,firstdetect,firstinput;
short get;
short formerlen,tmpstrlen;


char existapp[255][20];
char address[255][255];
char copyapp[255][20];
char tmp[255];

int main(int argc, char*argv[])
{
    _init();
    _run();
    return 0;
}


int _run()
{
	short _i,_select;
    char inputname[20];
    int backlen; 
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
			if(inputname[_i]=='\b')  //deal with the backspack key
			{
				backlen=formerlen;
				putchar('\b');
				while((formerlen--)>-1)
					putchar('\0');
				
				while((backlen--)>-1)
					putchar('\b');
					inputname[_i-1]=0; 
				_i-=2;
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
    				get=1;                
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
		printf("\n Add Mode:\n    Path:");
        gets(address[appcount+1]);
		printf("    Name :");
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
    printf("\(?-?)/");
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
