#include <stdio.h>
#include <stdlib.h>
#include "Init.h"
#include "Loop.h"
#include "FileHandler.h"
#include "System.h"

void printPenguins();

int main(int argc, char *argv[], char *env[])
{
    printPenguins();
    printf("\n");
    setRunning(1);
    //setSystem(env);
    sys = "mac";
#ifndef INTERACTIVE
    if(argc == 5) {
        char *phase = argv[1]+6;
        int penguins = atoi(argv[2]+9);
        char *input = argv[3];
        Init(phase, penguins, input);
    } else {
    setRunning(0);
    printf("NOT ENOUGH ARGUMENTS");
    }
#else
    if(argc == 1) {
        definePenguins();
        boardRandom();
        boardPrint();
    } else
    if(argc == 5) {
        char *phase = argv[1]+6;
        int penguins = atoi(argv[2]+9);
        char *input = argv[3];
        Init(phase, penguins, input);
    } else setRunning(0);

#endif
    while(running){
        Loop();
    }
    boardOut(argv[4]);
#ifndef INTERACTIVE
#endif // INTERACTIVE
    return 0;
}

void printPenguins() {
            printf(" _____  ______ _   _  _____ _    _ _____ _   _  _____ \n"
                           "|  __ \\|  ____| \\ | |/ ____| |  | |_   _| \\ | |/ ____|\n"
                           "| |__) | |__  |  \\| | |  __| |  | | | | |  \\| | (___  \n"
                           "|  ___/|  __| | . ` | | |_ | |  | | | | | . ` |\\___ \\ \n"
                           "| |    | |____| |\\  | |__| | |__| |_| |_| |\\  |____) |\n"
                           "|_|    |______|_| \\_|\\_____|\\____/|_____|_| \\_|_____/ ");
}