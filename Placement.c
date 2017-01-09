#include "Placement.h"
#include "FileHandler.h"
#include "Define.h"
#include "System.h"

void Placement(int player){
    int x, y, possiblePlacements;
    possiblePlacements = countPossiblePlacements();
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
                //here algorithm will tell x and y for penguin placement
                x = 1; y = 1;
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
