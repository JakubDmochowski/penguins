#include "Phase_Init.h"
#include "Phase_Placement.h"
#include "Phase_Movement.h"
#include "Phase_Loop.h"
#include "System.h"
#include "FileHandler.h"

void Init(char *Phase, int Penguins, char *input) {
    int i, valid = -1;
    char bufferClear;
    setPlayers(input);
    getBoardSize(input);
    score = (int *)calloc(nrOfPlayers, sizeof(int));
    board = (int **)calloc(BoardMX, sizeof(int));
    for(i = 0; i < BoardMX; i++){
        board[i] = (int *)calloc(BoardMY, sizeof(int));
    }
    boardLoad(input);
    scoreLoad(input);
    setPenguins(Penguins);
    setPhase(Phase);
    #ifdef INTERACTIVE
        scorePrint();
        boardPrint();
        computerPlayers = (int *)calloc(nrOfPlayers, sizeof(int));
        i = 0;
        do{
            do{
                if(valid == 0)printf("Wrong input, players belong to integrals (1 - %d)\n", nrOfPlayers);
                printf("Type which players should be controlled by AI (type 0 to end)\n");
                valid = scanf("%d", &computerPlayers[i]);
                if(computerPlayers[i] < 0 || computerPlayers[i] > nrOfPlayers) valid = 0;
                scanf("%c", &bufferClear); //clear buffer
            }while(!valid);
        }while(computerPlayers[i++] != 0);

    #else

    #endif //INTERACTIVE
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
