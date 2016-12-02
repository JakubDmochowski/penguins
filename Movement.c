#include "Movement.h"
#include "Define.h"
#include "FileHandler.h"

void Movement(int player){
    coordinates player1 = penguinsChoose(1);
    step movesAvailable[6];
    step *pointerMovesAvailable = movesAvailable;
    int numberOfPossibleMoves = checkFirstMove(player1, pointerMovesAvailable);

    printf("Possible moves:\n");
    for(int i = 0; i < numberOfPossibleMoves; i++) {
        printf("%d) On floe [%d,%d] (%s)\n", i + 1, movesAvailable[i].coordinates.x, movesAvailable[i].coordinates.y, movesAvailable[i].name);
    }

    do{
#ifdef INTERACTIVE
    break;
#else

        //here algorithm will tell x and y for penguin placement
#endif

    } while(1);
};

coordinates penguinsChoose(int player) {
    coordinates penguinsOfPlayer[10];

    int x, y, i, penguinsCount = 0;
    int chosenPenguin;
    for (y = 0; y < BOARD_SIZE_Y; y++) {
        for (x = 0; x < BOARD_SIZE_X; x++) {
            if (board[x][y] == player + 3) {
                penguinsOfPlayer[penguinsCount].x = x;
                penguinsOfPlayer[penguinsCount].y = y;
                penguinsCount++;
            }
        }
    }

    printf("Choose coordinates:\n");
    for(i = 0; i < penguinsCount; i++) {
            printf("%d) Penguin on [%d,%d]\n", i + 1, penguinsOfPlayer[i].x, penguinsOfPlayer[i].y);
    }

    printf("Enter a number of penguin:\n");
    scanf("%d\n", &chosenPenguin);

    printf("You've chosen penguin %d on [%d,%d]\n", chosenPenguin, penguinsOfPlayer[chosenPenguin - 1].x, penguinsOfPlayer[chosenPenguin -1].y);

    return penguinsOfPlayer[chosenPenguin - 1];
}

int isFloeValid (coordinates floe) {
    if (board[floe.x][floe.y] == 1 || board[floe.x][floe.y] == 2 || board[floe.x][floe.y] == 3)
        return 1;
    else
        return 0;
}

int addFloeToList(coordinates penguin, step *movesAvailable, int counter, int shiftX, int shiftY, char* name) {
    coordinates currentFloe;
    currentFloe.x = penguin.x + shiftX;
    currentFloe.y = penguin.y + shiftY;
    if (isFloeValid(currentFloe)) {
        (movesAvailable + counter)->coordinates.x = currentFloe.x;
        (movesAvailable + counter)->coordinates.y = currentFloe.y;
        (movesAvailable + counter)->name = name;
        (movesAvailable + counter)->stepForward.x = shiftX;
        (movesAvailable + counter)->stepForward.y = shiftY;
        counter++;
    }

    return counter;
}

int checkFirstMove(coordinates penguin, step *movesAvailable) {
    int counter = 0;

    //upper left
    counter = addFloeToList(penguin, movesAvailable, counter, 0, -1, "upper-left");
    //upper right
    counter = addFloeToList(penguin, movesAvailable, counter, 1, -1, "upper-right");
    //left
    counter = addFloeToList(penguin, movesAvailable, counter, -1, 0, "left");
    //right
    counter = addFloeToList(penguin, movesAvailable, counter, 1, 0, "right");
    //bottom left
    counter = addFloeToList(penguin, movesAvailable, counter, 0, 1, "bottom-left");
    //bottom right
    counter = addFloeToList(penguin, movesAvailable, counter, 1, 1, "bottom-right");

    return counter;
}