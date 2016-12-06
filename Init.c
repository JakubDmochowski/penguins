#include "Init.h"
#include "FileHandler.h"
#include "Placement.h"
#include "Movement.h"
#include "Loop.h"

void Init(char *Phase, int Penguins, char *input) {
    setPenguins(Penguins);
    setPhase(Phase);
    boardLoad(input);
    scoreLoad(input);
    scorePrint();
    boardPrint();
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
