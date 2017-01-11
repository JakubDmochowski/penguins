#ifndef _FILEHANDLER_
    #define _FILEHANDLER_

#include <stdio.h>
#include <stdlib.h>
#include "Define.h"

int nrOfPlayers;
int BoardMX;
int BoardMY;

int *score;
int **board;

void scoreLoad(char *filename);
void scoreAdd(int player, int amount);
void scorePrint();

void boardRandom();
void boardPrint();
void boardLoad(char *filename);
void boardOut(char *filename);
void setPlayers(char *filename);
void getBoardSize(char *filename);


#endif // _FILEHANDLER_
