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
int ifStepForward();
coordinates makeStepForwardCoordinates(coordinates penguin, coordinates step);

#endif // _MOVEMENT_
