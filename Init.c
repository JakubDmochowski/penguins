#include "Init.h"

void Init(char *Phase, int Penguins, char *input, char *output) {
    setPenguins(Penguins);
    setMoves(5);                //will be taken from the board
    setPhase(Phase);
    boardLoad(input);
    scoreLoad(input);
    //boardRandom();
    scorePrint();
    boardPrint();

    if(getPenguins() > 0) running = true;
    //input = fopen(InBoard, "r");
    //output = fopen(OutBoard, "w");
};

void definePenguins() {
    scanf("%d", &penguins);
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
