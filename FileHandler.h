#ifndef _FILEHANDLER_
    #define _FILEHANDLER_

#include <stdio.h>
#include <stdlib.h>
#include "Define.h"

FILE *input, *output;

void scoreLoad(void *filename);
void scoreAdd(int player, int amount);
void scorePrint();

void boardRandom();
void boardPrint();
void boardLoad(void *filename);
void boardOut(void *filename);

int score[NR_OF_PLAYERS];

int board[BOARD_SIZE_X][BOARD_SIZE_Y];

#endif // _FILEHANDLER_
