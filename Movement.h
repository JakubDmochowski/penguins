#ifndef _MOVEMENT_
    #define _MOVEMENT_

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
int addFloeToList(coordinates penguin, step *movesAvailable, int counter, int shiftX, int shiftY, char* name);
coordinates makeStep (coordinates penguin, coordinates floe, int player);
int moveChoose(int numberOfPossibleMoves);
int ifStepForward(coordinates step);
coordinates makeStepForwardCoordinates(coordinates penguin, step step);
step createMove(coordinates penguin, int shiftX, int shiftY, char* directionName);
step checkMove(coordinates penguin, char* name);

#endif // _MOVEMENT_
