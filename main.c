#include <stdio.h>
#include <stdlib.h>
#include "Init.h"
#include "Loop.h"
#include "FileHandler.h"

int main(int argc, char *argv[])
{
    running = true;
#ifndef INTERACTIVE
    if(argc == 5) {
        char *phase = argv[1]+6;
        int penguins = atoi(argv[2]+9);
        char *input = argv[3];
        char *output = argv[4];
        Init(phase, penguins, input, output);
    } else {
    running = false;
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
        char *output = argv[4];
        Init(phase, penguins, input, output);
    } else running = false;

#endif
    while(running){
        Loop();
    }
    return 0;
}
