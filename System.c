#include "System.h"

void setSystem(char *env[]){
    int i;
    char *ptr;
    char *os = "OS=";
    int system;
    system = MAC;
    for(i = 0; env[i] != 0; i++){
        ptr = strstr(env[i], os);
        if(ptr) {
            if(strcmp(ptr+3, "Windows_NT") == 0) system = WINDOWS;
        }
    }
}

int getSystem(){
    return sys;
}

void clearscr(void)
{
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
//add some other OSes here if needed
#else
    #error "OS not supported."
    //you can also throw an exception indicating the function can't be used
#endif
}
