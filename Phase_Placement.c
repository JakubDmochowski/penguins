#include "Phase_Placement.h"
#include "FileHandler.h"
#include "Phase_Init.h"
#include "Define.h"
#include "System.h"
#include "Phase_Movement.h"

void Placement(int player){
    int i, x, y, AI, possiblePlacements;
    //Variables to Algorithm:
    int j, k, counter, temp;
    double sum;
    Move move;
    Move *movesAvailable;
    struct best {
        double sum;
        coordinates cords;
    } best = {0, {0, 0}};
    possiblePlacements = countPossiblePlacements();
    AI = 0;

    do {
        if (possiblePlacements) {
        #ifdef INTERACTIVE

            for(i = 0; i < nrOfPlayers; i++){
                if(player == computerPlayers[i]) AI = 1;
            }
            if(AI == 0){
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
            } else {
                //Algorithm: Choose place on the board, when you can earn the most fishes around
                for (i = 1; i < BoardMY - 1; i++) {
                    for (j = 1; j < BoardMX - 1; j++) {
                        move.Penguin.x = j;
                        move.Penguin.y = i;
                        sum = 0;
                        if(board[j][i] != 1) continue;
                        temp = board[j][i];
                        board[j][i] = player;
                        counter = getPossibleMovesNumber(move.Penguin);
                        movesAvailable = (Move *)calloc(1, sizeof(Move));
                        movesAvailable = getPossibleMoves(move.Penguin);
                        for (k = 0; k < counter; k++) {
                            sum = movePotential(movesAvailable[k]);

                            if (sum > best.sum) {
                                best.cords = move.Penguin;
                                best.sum = sum;
                            }
                        }
                        board[j][i] = temp;
                    }
                }
                x = best.cords.x, y = best.cords.y;
            }
        #else
                //Algorithm: Choose place on the board, when you can earn the most fishes around
                for (i = 1; i < BoardMY - 1; i++) {
                    for (j = 1; j < BoardMX - 1; j++) {
                        move.Penguin.x = j;
                        move.Penguin.y = i;
                        sum = 0;
                        if(board[j][i] != 1) continue;
                        temp = board[j][i];
                        board[j][i] = player;
                        counter = getPossibleMovesNumber(move.Penguin);
                        movesAvailable = (Move *)calloc(1, sizeof(Move));
                        movesAvailable = getPossibleMoves(move.Penguin);
                        for (k = 0; k < counter; k++) {
                            sum = movePotential(movesAvailable[k]);

                            if (sum > best.sum) {
                                best.cords = move.Penguin;
                                best.sum = sum;
                            }
                        }
                        board[j][i] = temp;
                    }
                }
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
