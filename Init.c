#include "System.h"
#include "Init.h"
#include "FileHandler.h"
#include "Placement.h"
#include "Movement.h"
#include "Loop.h"


void Init(char *Phase, int Penguins, char *input) {
    int i;
    setPlayers(input);
    getBoardSize(input);
    score = (int *)malloc(nrOfPlayers * sizeof(int));
    board = (int **)malloc(BoardMX * sizeof(int));
    for(i = 0; i < BoardMX; i++){
        board[i] = (int *)malloc(BoardMY * sizeof(int));
    }
    boardLoad(input);
    scoreLoad(input);
    setPenguins(Penguins);
    setPhase(Phase);
    scorePrint();
    boardPrint();
};

void definePenguins() {
    do {
        if (penguins == ERROR) printf("Invalid data. Please try again.\n");
        printf("Type number of penguins:\n");
        penguins = getIntFromUser();
    } while (penguins == ERROR);
    clearscr();
};

int getPenguins(){
    return penguins;
}

void setPenguins(int number){
    penguins = number;
}

void setRunning(bool Running){
    running = Running;
}
