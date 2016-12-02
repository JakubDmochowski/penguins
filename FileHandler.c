#include "FileHandler.h"
#include <string.h>
#include <time.h>

void scoreLoad(void *filename){
    int player;
    int temp[1];
    char tmp[1];
    char Directory[64];
    //For mac
    strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    //For Windows
    //strcpy(Directory, "./");
    strcat(Directory, filename);
    input = fopen(Directory, "r");
    player = 0;
    do{
        fscanf(input, "%d", temp);
        score[player] = temp[0];
        player++;
        fscanf(input, "%c", tmp);
    }while(tmp[0] != ';');
    fclose(input);
}

void scoreAdd(int player, int amount){
    score[player - 1] += amount;
}

void scorePrint(){
    int i;
    for(i = 0; i < NR_OF_PLAYERS; i++){
        printf("P%d score:%d\n ", i, score[i]);
    }
    printf("\n");
}

void boardPrint() {
    int i, j;

    printf("\t");
    for (i = 0; i < BOARD_SIZE_X; i++) {
        if (i < 10)
            printf("   %d   %d", i, i);
        if (i >= 10)
            printf("  %d  %d", i, i);
    }
    printf("\n\n");

    for (i = 0; i < BOARD_SIZE_X; i++) {

        printf("\t");
        for (j = 0; j < BOARD_SIZE_Y; ++j) {

            if ((j == 0) && (i % 2))
                printf("    ");

            if (board[i][j] == 0)
                printf("        ");
            else
                printf(" /   \\  ");
        }
        printf("\n");

        printf("%d\t", i);
        for (j = 0; j < BOARD_SIZE_Y; ++j) {

            if ((j == 0) && (i % 2))
                printf("    ");

            if (board[i][j] == 0)
                printf("        ");
            else if (board[i][j] > 3)
                printf("| P %d | ", (board[i][j]) - 3);
            else
                printf("|  %d  | ", board[i][j]);

        }

        printf("\n");

        printf("\t");
        for (j = 0; j < BOARD_SIZE_Y; ++j) {

            if ((j == 0) && (i % 2))
                printf("    ");

            if (board[i][j] == 0)
                printf("        ");
            else
                printf(" \\___/  ");
        }
        printf("\n");
    }
}

void boardRandom() {
    int i, j;
    srand(time(NULL));
    for (i = 0; i < BOARD_SIZE_Y; i++) {
        for (j = 0; j < BOARD_SIZE_X; ++j) {
            board[i][j] = rand() % 6;
        }
    }
}


void boardLoad(void *filename){
    int i, j;
    char temp;
    char Directory[64];
    //For mac
    strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    //For Windows
    //(Directory, "./");
    strcat(Directory, filename);
    input = fopen(Directory, "r");
    if (input == NULL) {
        printf("Error");
        return;
    }
    i = 0;
    j = 0;
    //ignores score in file reading
    while(temp != ';'){
        fscanf(input, "%c", &temp);
    }
    fscanf(input, "%c", &temp);

    while(fscanf(input, "%c", &temp) != EOF){
        if(temp == ',') continue;
        if(temp == ';'){
            i++;
            j = 0;
            fscanf(input, "%c", &temp);
            continue;
        }
        board[i][j] = (temp - '0');
        j++;
    }
    fclose(input);
}
