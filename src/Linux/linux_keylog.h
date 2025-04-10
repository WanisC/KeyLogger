#include <stdio.h>

#ifndef LIN_KEYLOG_H
#define LIN_KEYLOG_H

#define KEY_MAX_CODE 256

void update_modifier_keys(int code, int value);
const char* translate_key(int code);

void linWriteHeader(const char* filePath);
void lin_keylog(const char* filePath);
void end_keylog(const char* filePath);

#endif // LIN_KEYLOG_H