#include "Loop.h"
#include "FileHandler.h"
#include "Placement.h"
#include "Movement.h"
#include "Define.h"

phase = PLACEMENT;
turn = 1;

void setPhase(char *P){
    if(strcmp(P, "movement") == 0) phase = MOVEMENT;
    if(strcmp(P, "placement") == 0) phase = PLACEMENT;
}

void Loop(){                                        //during one round we place or move penguins
    //GetCommands();
    if(phase == PLACEMENT){
        Placement(((turn - 1) % NR_OF_PLAYERS) + 1);
        #ifdef INTERACTIVE
        scorePrint();
        boardPrint();
        #else
        #endif
        if((getPenguins() == (turn / NR_OF_PLAYERS)) && ((turn % NR_OF_PLAYERS == 0))) phase = MOVEMENT;
        turn++;
    }
    if(phase == MOVEMENT) {
        Movement(((turn - 1) % NR_OF_PLAYERS) + 1);
        setRunning(0);
    }
};
