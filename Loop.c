#include "Loop.h"
#include "FileHandler.h"
#include "Placement.h"
#include "Movement.h"
#include "Define.h"
#include "Init.h"
#include "System.h"

#include <string.h>

phase = PLACEMENT;
turn = 1;

void setPhase(char *P){
    if(strcmp(P, "movement") == 0) phase = MOVEMENT;
    if(strcmp(P, "placement") == 0) phase = PLACEMENT;
}

void Loop(){
    int x,y,z, penguinsCount, winner = 0;

    if(phase == PLACEMENT){
        Placement(((turn - 1) % NR_OF_PLAYERS) + 1);
#ifdef INTERACTIVE
        clearscr();
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
        clearscr();
        scorePrint();
        boardPrint();
#else
#endif
        turn++;

        //calculate quantity of penguins on whole board
        penguinsCount = 0;
        for (z = 1; z <= NR_OF_PLAYERS; z++) {
            for (y = 0; y < BOARD_SIZE_Y; y++) {
                for (x = 0; x < BOARD_SIZE_X; x++) {
                    if (board[x][y] == z + 3) {
                        penguinsCount++;
                    }
                }
            }
        }

        if(penguinsCount == 0)   {
            setRunning(0);
            clearscr();
            printGameOver();

            for (z = 0; z < NR_OF_PLAYERS; z++) {
                if (score[z] > score[winner])
                    winner = z;
            }
            printf("\n\n\n\nThe winner is PLAYER %d with score %d!\n\n\n\n", winner + 1, score[winner]);
        }
    }
};

void printGameOver() {
            printf("  _____          __  __ ______    ______      ________ _____  \n"
                   " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n"
                   "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n"
                   "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / \n"
                   "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n"
                   " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\\n");
}
