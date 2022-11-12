#if defined(_WIN32)
  #define OS_WIN
#elif defined(_MAC)
  #define OS_MAC
#elif defined(__GNUG__) || defined(__GNUC__)
  #define OS_LINUX
#endif

#ifdef OS_WIN
#include <conio.h>
#elif defined(OS_LINUX) || defined(OS_MAC)
#include "sys/ioctl.h"
#include "termios.h"
#endif

#include "stdio.h"
#include "time.h"


namespace internal {

static const int STDIN=0;
static bool initialized = false;

// Comment ca va 

int keyEvent(){
    #if defined(OS_WIN)
    // this works by harnessing Windows' black magic:
    return _kbhit();
#   elif defined(OS_LINUX) || defined(OS_MAC) 

    if( !initialized){
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    //int bytesWaiting;                                                                                                                                                        
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
    #endif
}

void frameSleep(const int& ms){
    clock_t end;
    end = clock() + ms * CLOCKS_PER_SEC/1000;
    while( clock() < end){
        // wait 
    }
}

}