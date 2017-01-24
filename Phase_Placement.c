#include "Phase_Placement.h"
#include "FileHandler.h"
#include "Define.h"
#include "System.h"
#include "Phase_Movement.h"

void Placement(int player){
    int x, y, possiblePlacements;
    possiblePlacements = countPossiblePlacements();
    //Variables to Algorithm:
    #ifndef INTERACTIVE
    int i, j, k, counter, sum;
    coordinates move;
    step movesAvailable[6];
    step *pointerMovesAvailable = movesAvailable;
    struct best {
        int sum;
        coordinates cords;
    } best = {0, {0, 0}};
    #endif


    do {
        if (possiblePlacements) {
        #ifdef INTERACTIVE
            do {
                if (x == ERROR) printf("Invalid data. Please try again.\n");
                printf("Enter the X coordinate:\n");
                x = getIntFromUser();
            } while (x == ERROR);

            do {
                if (y == ERROR) printf("Invalid data. Please try again.\n");
                printf("Enter the Y coordinate:\n");
                y = getIntFromUser();
            } while (y == ERROR);

            if(x == -1 && y == -1)return;
            clearscr();
            #else
                //Algorithm: Choose place on the board, when you can earn the most fishes around
                for (i = 1; i < BoardMY - 1; i++) {
                    for (j = 1; j < BoardMX - 1; j++) {
                        move.x = j;
                        move.y = i;
                        sum = 0;

                        counter = checkFirstMove(move, pointerMovesAvailable);

                        for (k = 0; k < counter; k++) {
                            sum += board[(movesAvailable+k)->coordinates.x][(movesAvailable+k)->coordinates.y];

                            if (sum > best.sum) {
                                best.cords = move;
                                best.sum = sum;
                            }
                        }
                    }
                }
                printf("Penguin will move on [%d,%d]\n", best.cords.x, best.cords.y);
                x = best.cords.x, y = best.cords.y;
            #endif
            if (placementValid(x, y)) {
                placePenguin(player, x, y);
                possiblePlacements--;
                return;
            } else {
                scorePrint();
                boardPrint();
                printf("Invalid Move\n");
            }
        } else {
            printf("No more placement options.\n");
            setPhase("Movement");
            break;
        }
            setRunning(0);
        break;
    } while(1);
};

void placePenguin(int player,int x, int y){
    scoreAdd(player, board[x][y]);
    board[x][y] = player + 3;
}

int placementValid(int x, int y){
    return board[x][y] == 1;
}

int countPossiblePlacements(){
    int x;
    int y;
    int count = 0;
    for (y = 0; y < BoardMY; y++) {
        for (x = 0; x < BoardMX; x++) {
            if (board[x][y] == 1) {
                count++;
            }
        }
    }
    return count;
}
