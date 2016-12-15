#ifndef _SYSTEM_
    #define _SYSTEM_

enum{
    WINDOWS,
    MAC
};

int sys;

void setSystem(char *env[]);
int getSystem();
void clearscr(void);
int getIntFromUser();


#endif // _SYSTEM_
