#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "System.h"

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

int getIntFromUser() {
    char *stringNumber = malloc(3);
    char c;
    int i = 0, currentSize = 3, flag = 0;
    int number;

    while (( c = getchar() ) != '\n' && c != EOF ) {
        if (c == '+' && i == 0) {

        } else {
            if (c > 47 && c < 58) {
                stringNumber[i++] = c;
            } else {
                flag = 1;
            }
        }

        if(i == currentSize)
        {
            currentSize = i + sizeof(char);
            stringNumber = realloc(stringNumber, currentSize);
        }
    }
    stringNumber[i] = '\0';
    number = atoi(stringNumber);
    free(stringNumber);

    fflush(stdin);

    if (flag)
        return -11;
    else
        return number;
}
