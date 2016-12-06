#include <stdio.h>
#include <stdlib.h>
#include "Init.h"
#include "Loop.h"
#include "FileHandler.h"
#include "System.h"

int main(int argc, char *argv[], char *env[])
{
    setRunning(1);
    setSystem(env);
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
