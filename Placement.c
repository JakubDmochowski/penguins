#include "Placement.h"
#include "FileHandler.h"
#include "Define.h"
#include "System.h"

void Placement(int player){
    int x, y;
    do{
        #ifdef INTERACTIVE
        printf("Type coordinates of place to put penguin: (X Y) (-1 -1 if no moves are possible)\n");
        scanf("%d %d", &x, &y);
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
