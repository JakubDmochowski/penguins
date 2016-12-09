#ifndef _SYSTEM_
    #define _SYSTEM_

enum{
    WINDOWS,
    MAC
};

int sys;

void setSystem(char *env[]);
int getSystem();

#endif // _SYSTEM_
