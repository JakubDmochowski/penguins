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
