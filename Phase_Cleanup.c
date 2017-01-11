#include "Phase_Cleanup.h"
#include "FileHandler.h"

void Cleanup(){
    int i;
    free(score);
    for(i = 0; i < BoardMX; i++){
        free(board[i]);
    }
    free(board);
}
