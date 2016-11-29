#include "Placement.h"
#include "FileHandler.h"

void Placement(){
    printf("Placement phase here\n");
    placePenguin(1, 1, 1);
    setPenguins(getPenguins() - 1);
};

void placePenguin(int player,int x, int y){
    if(board[y][x] > 1){
        printf("Invalid Move\n");
        return;
    }
    scoreAdd(player, board[y][x]);
    board[y][x] = player + 3;
}
