#ifndef _PHASE_MOVEMENT_
    #define _PHASE_MOVEMENT_

typedef struct {
    int x;
    int y;
} coordinates;

typedef struct {
    coordinates coordinates;
    coordinates stepForward;
    char* name;
} step;

void Movement(int player);
coordinates penguinsChoose(int player);
int isFloeValid (coordinates floe);
int checkFirstMove(coordinates penguin, step *movesAvailable);
coordinates makeStep (coordinates penguin, coordinates floe, int player);
int moveChoose(int numberOfPossibleMoves);
int ifStepForward(coordinates step);
coordinates makeStepForwardCoordinates(coordinates penguin, step step);
step createMove(coordinates penguin, int shiftX, int shiftY, char* directionName);
step checkMove(coordinates penguin, char* name);
void penguinDelete(coordinates penguin);

#endif // _PHASE_MOVEMENT_
