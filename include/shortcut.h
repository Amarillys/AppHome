//the header that save the funtions of  loading and managing shortcuts
#include "base.h"

void AddShortCut(struct App ShortCut[],short *AppCount);
void AntiFill(short length);
short AutoFill(int length, char EntireStr[],bool WillBack);
void LoadShortCut(struct App ShortCut[],short *appcount);
bool DetectChar(char InputChar[], short *ResultIndex, struct App ShortCut[], short *appcount);
