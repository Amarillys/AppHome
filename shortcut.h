//the header that save the funtions of  loading and managing shortcuts
#include "base.h"

void AddShortCut(struct App ShortCut[],short *appcount);
void AntiFill(short length);
short AutoFill(int length, char EntireStr[]);
void LoadShortCut(struct App ShortCut[],short *appcount);
bool DetectChar(char InputChar[], short *ResultIndex, struct App ShortCut[], short *appcount);
