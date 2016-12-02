#include "Init.h"
#include "FileHandler.h"
#include "Placement.h"
#include "Movement.h"
#include "Loop.h"

void Init(char *Phase, int Penguins, char *input, char *output) {
    setPenguins(Penguins);
    setPhase(Phase);
    boardLoad(input);
    scoreLoad(input);
    scorePrint();
    boardPrint();
    //input = fopen(InBoard, "r");
    //output = fopen(OutBoard, "w");
};

void definePenguins() {
    printf("Type number of penguins:\n");
    scanf("%d", &penguins);
    system("cls");
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
