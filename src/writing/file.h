#include <stdio.h>

int CheckLogFolder(const char *chemin);
void CreateLogFolder(const char *chemin);
void WriteIntoFile(char data, const char* filePath);
void WriteSpecialKeyIntoFile(char *data, const char* filePath);