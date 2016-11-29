#include "Init.h"
#include "Loop.h"

int main(int argc, char *argv[])
{
    if(argc == 1) {
            // temporary, here we'll have interactive mode
        running = false;
    } else
    if(argc == 5) {
        char *phase = argv[1]+6;
        int penguins = atoi(argv[2]+9);
        char *input = argv[3];
        char *output = argv[4];
        Init(phase, penguins, input, output);
    } else
    running = false;

    while(running){
        Loop();
    }
    return 0;
}
