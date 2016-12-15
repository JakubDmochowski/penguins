#include "Placement.h"
#include "FileHandler.h"
#include "Define.h"
#include "System.h"

void Placement(int player){
    int x, y;
    do {
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
        #endif
        if(placementValid(x, y)) {
            placePenguin(player, x, y);
            return;
        } else {
            scorePrint();
            boardPrint();
            printf("Invalid Move\n");
        }
    } while(1);
};

void placePenguin(int player,int x, int y){
    scoreAdd(player, board[x][y]);
    board[x][y] = player + 3;
}

int placementValid(int x, int y){
    return board[x][y] == 1;
}