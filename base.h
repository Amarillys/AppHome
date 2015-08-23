#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#ifndef APP_STRUCT
#define APP_STRUCT

#define true 1
#define false 0

struct App{
	char Name[20];
	char Path[255];
};

struct EnWord{
	char Word[32];
	int Offset;
};

typedef unsigned char bool;
typedef unsigned char uint8;

#endif