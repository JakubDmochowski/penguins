#ifndef _FILEHANDLER_
    #define _FILEHANDLER_

#include <stdio.h>
#include <stdlib.h>
#include "Define.h"

FILE *input, *output;

int nrOfPlayers;
int BoardMX;
int BoardMY;

int *score;
int **board;

void scoreLoad(void *filename);
void scoreAdd(int player, int amount);
void scorePrint();

void boardRandom();
void boardPrint();
void boardLoad(void *filename);
void boardOut(void *filename);
void setPlayers(void *filename);
void getBoardSize(char *filename);


#endif // _FILEHANDLER_
