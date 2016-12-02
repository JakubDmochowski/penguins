#include "Placement.h"

void Placement(){
    printf("Placement phase here\n");
    userPlacePenguin();
    setPenguins(getPenguins() - 1);
    scorePrint();
    boardPrint();
};

void userPlacePenguin() {
    int x,y, isCorrect = 0;
    do {
        printf("Where would you like to place penguin?\n");
        printf("Please enter coordinate X:\n");
        scanf("%d\n", &x);
        printf("Please enter coordinate Y:\n");
        scanf("%d\n", &y);

        isCorrect = placePenguin(1, y, x);

        if (isCorrect == 1) {
            printf("You gave invalid cooridnates. Please try again.\n");
        }
    } while (isCorrect);

}

int placePenguin(int player,int x, int y) {
    if(board[y][x] != 1){
        return 1;
    }
    scoreAdd(player, board[y][x]);
    board[y][x] = player + 3;
    return 0;
}
