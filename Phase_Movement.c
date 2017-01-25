#include "Phase_Movement.h"
#include "Phase_Init.h"
#include "Define.h"
#include "FileHandler.h"

#include "String.h"
#include "System.h"
#include "math.h"

void Movement(int player){
#ifdef INTERACTIVE
        int i, AI;
        static int lastFloeScore = 0;
        coordinates penguinToMove;
        coordinates lastPenguinPosition;
        step movesAvailable[6];
        step *pointerMovesAvailable = movesAvailable;
        int numberOfPossibleMoves;
        int chosenMove;
        char *chosenMoveName;
        step move;
        AI = 0;

        //Print an info
        printf("Turn of P%d\n", player);
        for(i = 0; i < nrOfPlayers; i++){
            if(player == computerPlayers[i]) AI = 1;
        }
        if(AI == 0){
            //Choose a penguin to move
            penguinToMove = penguinsChoose(player);
            numberOfPossibleMoves = checkFirstMove(penguinToMove, pointerMovesAvailable);
            while (1) {
                if (numberOfPossibleMoves != 0) {
                    printf("Possible moves:\n");
                    for (i = 0; i < numberOfPossibleMoves; i++) {
                        printf("%d) On floe [%d,%d] (%s)\n", i + 1, movesAvailable[i].coordinates.x,
                               movesAvailable[i].coordinates.y, movesAvailable[i].name);
                    }

                    //Choose a direction
                    chosenMove = moveChoose(numberOfPossibleMoves);
                    chosenMoveName = movesAvailable[chosenMove - 1].name; //needed for next moves

                    //Move penguin first time
                    lastPenguinPosition = penguinToMove;
                    board[lastPenguinPosition.x][lastPenguinPosition.y] = lastFloeScore;
                    lastFloeScore = board[movesAvailable[chosenMove - 1].coordinates.x][movesAvailable[chosenMove - 1].coordinates.y];
                    penguinToMove = makeStep(penguinToMove, movesAvailable[chosenMove - 1].coordinates, player);
                    //Print board
                    scorePrint();
                    boardPrint();

                    //Rest of the moves
                    move = checkMove(penguinToMove, chosenMoveName);
                    while (ifStepForward(makeStepForwardCoordinates(penguinToMove, move))) {
                        lastPenguinPosition = penguinToMove;
                        board[lastPenguinPosition.x][lastPenguinPosition.y] = lastFloeScore;
                        scoreAdd(player, -lastFloeScore);
                        lastFloeScore = board[move.coordinates.x][move.coordinates.y];
                        penguinToMove = makeStep(lastPenguinPosition, move.coordinates, player);
                        move = checkMove(penguinToMove, chosenMoveName);
                        scorePrint();
                        boardPrint();
                    }
                    lastFloeScore = 0;
                    break;
                } else {
                    printf("This penguin has no moves.\nPlease choose another penguin.\n");
                    penguinDelete(penguinToMove);
                    penguinToMove = penguinsChoose(player);

                    if (penguinToMove.x != -1 && penguinToMove.y != -1)
                        numberOfPossibleMoves = checkFirstMove(penguinToMove, pointerMovesAvailable);
                    else
                        printf("You have no penguins.\n");
                        break;
                }
            }
        } else {
            Move bestMove;
            bestMove = getBestMove(player);
            if(bestMove.destination.x != -1){
                makeStep(bestMove.Penguin, bestMove.destination, player);
                board[bestMove.Penguin.x][bestMove.Penguin.y] = 0;
            }

        }
#else
    Move bestMove;
    bestMove = getBestMove(player);
    if(bestMove.destination.x == -1) continue;
    makeStep(bestMove.Penguin, bestMove.destination, player);
    board[bestMove.Penguin.x][bestMove.Penguin.y] = 0;
#endif
};

coordinates penguinsChoose(int player) {
    coordinates penguinsOfPlayer[getPenguins()];
    coordinates error = {-1, -1};

    int x, y, i, penguinsCount = 0;
    int chosenPenguin;
    for (y = 0; y < BoardMY; y++) {
        for (x = 0; x < BoardMX; x++) {
            if (board[x][y] == player + 3) {
                penguinsOfPlayer[penguinsCount].x = x;
                penguinsOfPlayer[penguinsCount].y = y;
                penguinsCount++;
            }
        }
    }

    if (penguinsCount == 0) {
        return error;
    } else {
        printf("Choose coordinates:\n");
        for (i = 0; i < penguinsCount; i++) {
            printf("%d) Penguin on [%d,%d]\n", i + 1, penguinsOfPlayer[i].x, penguinsOfPlayer[i].y);
        }

        do {
            do {
                if (chosenPenguin == ERROR) printf("Invalid data. Please try again.\n");
                printf("Enter a number of penguin:\n");
                chosenPenguin = getIntFromUser();
            } while (chosenPenguin == ERROR);

            if (chosenPenguin > penguinsCount || chosenPenguin <= 0)
                printf("Invalid number, please try again.\n");
        } while (chosenPenguin > penguinsCount || chosenPenguin <= 0);

        printf("You've chosen penguin %d on [%d,%d]\n", chosenPenguin, penguinsOfPlayer[chosenPenguin - 1].x,
               penguinsOfPlayer[chosenPenguin - 1].y);

        return penguinsOfPlayer[chosenPenguin - 1];
    }
}

int moveChoose(int numberOfPossibleMoves) {
    int move;

    do {
        do {
            if (move == ERROR) printf("Invalid data. Please try again.\n");
            printf("Please choose your first move:\n");
            move = getIntFromUser();
        } while (move == ERROR);

        if (move <= 0 || move > numberOfPossibleMoves)
            printf("Invalid number, please try again.\n");
    } while (move <= 0 || move > numberOfPossibleMoves);

    return move;

}

int isFloeValid (coordinates floe) {
    if (floe.x >= 0 && floe.y >= 0 && floe.x < BoardMX && floe.y < BoardMY) {
        if (board[floe.x][floe.y] == 1 || board[floe.x][floe.y] == 2 || board[floe.x][floe.y] == 3)
            return 1;
        else
            return 0;
    } else
        return 0;
}

int checkFirstMove(coordinates penguin, step *movesAvailable) {
    int counter = 0, i;
    char* names[6] = {"upper-left", "upper-right", "left", "right", "bottom-left", "bottom-right"};
    step tempStep;

    for (i = 0; i < 6; i++) {
        tempStep = checkMove(penguin, names[i]);
        if (strcmp(tempStep.name, "error")) {
            *(movesAvailable + counter) = tempStep;
            counter++;
        }
    }

    return counter;
}

step checkMove(coordinates penguin, char* name) {
    if (!strcmp(name, "upper-left")) {
        switch (penguin.y % 2) {
            case 0:
                return createMove(penguin, -1, -1, "upper-left");
            case 1:
                return createMove(penguin, 0, -1, "upper-left");
        }
    }

    if (!strcmp(name, "upper-right")) {
        switch (penguin.y % 2) {
            case 0:
                return createMove(penguin, 0, -1, "upper-right");
            case 1:
                return createMove(penguin, 1, -1, "upper-right");
        }
    }

    if (!strcmp(name, "left")) {
        return createMove(penguin, -1, 0, "left");
    }

    if (!strcmp(name, "right")) {
        return createMove(penguin, 1, 0, "right");
    }

    if (!strcmp(name, "bottom-left")) {
        switch (penguin.y % 2) {
            case 0:
                return createMove(penguin, -1, 1, "bottom-left");
            case 1:
                return createMove(penguin, 0, 1, "bottom-left");
        }
    }

    if (!strcmp(name, "bottom-right")) {
        switch (penguin.y % 2) {
            case 0:
                return createMove(penguin, 0, 1, "bottom-right");
            case 1:
                return createMove(penguin, 1, 1, "bottom-right");
        }
    }
}

step createMove(coordinates penguin, int shiftX, int shiftY, char* directionName) {
    step step;
    coordinates currentFloe;
    currentFloe.x = penguin.x + shiftX;
    currentFloe.y = penguin.y + shiftY;
    if (isFloeValid(currentFloe)) {
        step.coordinates.x = currentFloe.x;
        step.coordinates.y = currentFloe.y;
        step.name = directionName;
        step.stepForward.x = shiftX;
        step.stepForward.y = shiftY;
    } else {
        step.coordinates.x = -1;
        step.coordinates.y = -1;
        step.name = "error";
    }

    return step;
    }

int ifStepForward(coordinates step) {
    char choice;

    if(isFloeValid(step)) {
        while(1) {
                printf("Would you like to do another step? (y/n)\n");
                scanf(" %c", &choice);

                switch (choice) {
                    case 'y':
                        return 1;
                    case 'n':
                        return 0;
                    default:
                        printf("Invalid choice. Please try again\n");
                }
        }
    } else {
        printf("No more moves in this direction available.\n");
        return 0;
    }
}

coordinates makeStepForwardCoordinates(coordinates penguin, step step) {
    coordinates finalCoordinates;

    finalCoordinates.x = penguin.x + step.stepForward.x;
    finalCoordinates.y = penguin.y + step.stepForward.y;

    return finalCoordinates;
}

coordinates makeStep (coordinates penguin, coordinates floe, int player) {
    coordinates newPenguinPlace;
    newPenguinPlace.x = floe.x;
    newPenguinPlace.y = floe.y;

    scoreAdd(player, board[floe.x][floe.y]);
    board[floe.x][floe.y] = player + 3;
    return newPenguinPlace;
}

void penguinDelete(coordinates penguin) {
    board[penguin.x][penguin.y] = 0;
}

Move getBestMove(int player){
    int i, x, y, nrOfMovesPossible;
    Move bestMove;
    int nrOfPenguins = 0;
    penguin *penguins;
    Move *possibleMoves;
    double bestMoveValue = 0;
    double moveValue = 0;
    bestMove.destination.x = -1;
    bestMove.destination.y = -1;
    penguins = (penguin *)malloc(nrOfPenguins * sizeof(penguin));
    if(penguins == null){
        printf("Memory Allocation error in function getBestMove\n");
        exit(2);
    }
    possibleMoves = (Move *)malloc(sizeof(Move));
    if(possibleMoves == null){
        printf("Memory Allocation error in function getBestMove\n");
        exit(2);
    }
    for(x = 0; x < BoardMX; x++){
        for(y = 0; y < BoardMY; y++){
            if(board[x][y] == player + 3) {
                penguins = (penguin *)realloc(penguins, ++nrOfPenguins * sizeof(penguin));
                penguins[nrOfPenguins - 1].coordinates.x = x;
                penguins[nrOfPenguins - 1].coordinates.y = y;
                penguins[nrOfPenguins - 1].ID = nrOfPenguins - 1;
            }
        }
    }
    if(nrOfPenguins == 0) {
        return bestMove;
    }
    for(i = 0; i < nrOfPenguins; i++){
        possibleMoves = getPossibleMoves(penguins[i].coordinates);
        nrOfMovesPossible = getPossibleMovesNumber(penguins[i].coordinates);
        if(nrOfMovesPossible == 0){
            penguinDelete(penguins[i].coordinates);
            continue;
        }
        for(x = 0; x < nrOfMovesPossible; x++){
            moveValue = movePotential(possibleMoves[x]);
            if(moveValue > bestMoveValue) {
                bestMoveValue = moveValue;
                bestMove.Penguin = penguins[i].coordinates;
                bestMove.destination = possibleMoves[x].destination;
            }
        }
    }
    return bestMove;
}

Move *getPossibleMoves(coordinates Coords){
    Move *PossibleMoves;
    step temp;
    step *Moves;
    int nrOfMoves = 6;
    int i;
    Moves = (step *)calloc(nrOfMoves, sizeof(step));
    if(Moves == null){
        printf("Memory Allocation error in function getPossibleMoves\n");
        exit(2);
    }
    nrOfMoves = checkFirstMove(Coords, Moves);
    if(nrOfMoves == 0) return null;
    Moves = (step *)realloc(Moves, nrOfMoves * sizeof(step));
    if(Moves == null){
        printf("Memory Reallocation error in function getPossibleMoves\n");
        exit(2);
    }
    for(i = 0; i < nrOfMoves; i++){
        temp = checkMove(Moves[i].coordinates, Moves[i].name);
        if(isFloeValid(temp.coordinates)){
            nrOfMoves++;
            Moves = (step *)realloc(Moves, nrOfMoves * sizeof(step));
            if(Moves == null){
                printf("Memory Reallocation error in function getPossibleMoves\n");
                exit(2);
            }
            Moves[nrOfMoves - 1] = temp;
        }
    }
    PossibleMoves = (Move *)malloc(nrOfMoves * sizeof(Move));
    for(i = 0; i < nrOfMoves; i++){
        PossibleMoves[i].Penguin.x = Moves[i].coordinates.x - Moves[i].stepForward.x;
        PossibleMoves[i].Penguin.y = Moves[i].coordinates.y - Moves[i].stepForward.y;
        PossibleMoves[i].destination.x = Moves[i].coordinates.x;
        PossibleMoves[i].destination.y = Moves[i].coordinates.y;
        free(Moves[i].name);
    }
    free(Moves);
    return PossibleMoves;
}

int getPossibleMovesNumber(coordinates Coords){
    step temp;
    step *M;
    int nrOfMoves = 6;
    int i;
    M = (step *)malloc(nrOfMoves * sizeof(step));
    if(M == null){
        printf("Memory Allocation error in function getPossibleMovesNumber\n");
        exit(2);
    }
    nrOfMoves = checkFirstMove(Coords, M);
    if(nrOfMoves == 0) return 0;
    M = (step *)realloc(M, nrOfMoves * sizeof(step));
    if(M == null){
        printf("Memory Reallocation error in function getPossibleMovesNumber\n");
        exit(2);
    }
    for(i = 0; i < nrOfMoves; i++){
        temp = checkMove(M[i].coordinates, M[i].name);
        if(isFloeValid(temp.coordinates)){
            nrOfMoves++;
            M = (step *)realloc(M, nrOfMoves * sizeof(step));
            if(M == null){
                printf("Memory Reallocation error in function getPossibleMovesNumber\n");
                exit(2);
            }
            M[nrOfMoves - 1] = temp;
        }
    }
    for(i = 0; i < nrOfMoves; i++){
        free(M[i].name);
    }
    free(M);
    return nrOfMoves;
}

double movePotential(Move Mv){
    Move *possibleMoves;
    double MovePotential = 0;
    int i;
    int nrOfMoves;
    possibleMoves = getPossibleMoves(Mv.destination);
    if(possibleMoves == null){
        MovePotential += board[Mv.destination.x][Mv.destination.y];
        return MovePotential;
    }
    nrOfMoves = getPossibleMovesNumber(Mv.destination);
    for(i = 0; i < nrOfMoves; i++){
        MovePotential += board[possibleMoves[i].destination.x][possibleMoves[i].destination.y];
    }
    MovePotential = sqrt(MovePotential);
    MovePotential += board[Mv.destination.x][Mv.destination.y];
    return MovePotential;
}
