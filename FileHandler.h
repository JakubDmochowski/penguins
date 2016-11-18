#ifndef _FILEHANDLER_
    #define _FILEHANDLER_

#include <stdio.h>
#include <stdlib.h>

#define NR_OF_PLAYERS 2

#define BOARD_SIZE_X 10
#define BOARD_SIZE_Y 10

FILE *input, *output;

void scoreLoad(void *filename);
void scorePrint();

void boardRandom();
void boardPrint();
void boardLoad(void *filename);

int score[NR_OF_PLAYERS];

int board[BOARD_SIZE_X][BOARD_SIZE_Y];

#endif // _FILEHANDLER_
