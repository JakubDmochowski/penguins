#include "Loop.h"
#include "FileHandler.h"
#include "Placement.h"
#include "Movement.h"
#include "Define.h"
#include "Init.h"

phase = PLACEMENT;
turn = 1;

void setPhase(char *P){
    if(strcmp(P, "movement") == 0) phase = MOVEMENT;
    if(strcmp(P, "placement") == 0) phase = PLACEMENT;
}

void Loop(){
    if(phase == PLACEMENT){
        Placement(((turn - 1) % NR_OF_PLAYERS) + 1);
#ifdef INTERACTIVE
        scorePrint();
        boardPrint();
#else
#endif
        //each player used all his possible penguins => next phase
        if((getPenguins() == (turn / NR_OF_PLAYERS)) && ((turn % NR_OF_PLAYERS == 0))) phase = MOVEMENT;
        turn++;
    }
    if(phase == MOVEMENT) {
        Movement(((turn - 1) % NR_OF_PLAYERS) + 1);

#ifdef INTERACTIVE
        scorePrint();
        boardPrint();
#else
#endif
        turn++;
        if(turn == 6)   {
            setRunning(0);
            printGameOver();
        }
    }
};

void printGameOver() {
            printf("  _____          __  __ ______    ______      ________ _____  \n"
                   " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n"
                   "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n"
                   "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / \n"
                   "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n"
                   " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
}
