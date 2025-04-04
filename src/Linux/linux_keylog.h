#include <stdio.h>

#ifndef LIN_KEYLOG_H
#define LIN_KEYLOG_H

void linWriteHeader(const char* filePath);
void lin_keylog(const char* filePath);
void end_keylog(const char* filePath);

#endif // LIN_KEYLOG_H