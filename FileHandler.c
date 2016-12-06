#include <string.h>
#include <time.h>
#include "FileHandler.h"
#include "Define.h"
#include "System.h"

void scoreLoad(void *filename){
    int player;
    int temp[1];
    char tmp[1];
    char Directory[64];

    if(sys == WINDOWS) strcpy(Directory, "./");
    else strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");

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
    printf("\nSCORES:\n");
    for(i = 0; i < NR_OF_PLAYERS; i++){
        printf("|   P%d: %d   |", i+1, score[i]);
    }
    printf("\n\n");
}


void boardPrint() {
    int x, y, score = 0;

    //Prints column's numbers
    printf("\t");
    for (x = 0; x < BOARD_SIZE_X; x++, score = 0) {
        for (y = 0; y < BOARD_SIZE_Y; y++) {
            score += board[x][y];
        }
        if (score != 0) {
            if (x < 10)
                printf("   %d   %d", x, x);
            if (x >= 10)
                printf("  %d  %d", x, x);
        }
    }
    printf("\n\n");

    for (y = 0; y < BOARD_SIZE_Y; y++) {
        for (x = 0, score = 0; x < BOARD_SIZE_Y; x++) {
            score += board[x][y];
        }

       if (score != 0) {
            printf("\t");
            for (x = 0; x < BOARD_SIZE_X; ++x) {

                if ((x == 0) && (y % 2))
                    printf("    ");

                if (board[x][y] == 0)
                    printf("        ");
                else
                    printf(" /   \\  ");
            }
            printf("\n");

            //Prints row's numbers
            printf("%d\t", y);


            for (x = 0; x < BOARD_SIZE_X; ++x) {

                if ((x == 0) && (y % 2))
                    printf("    ");

                if (board[x][y] == 0)
                    printf("        ");
                else if (board[x][y] > 3)
                    printf("| P %d | ", (board[x][y]) - 3);
                else
                    printf("|  %d  | ", board[x][y]);

            }

            printf("\n");

            printf("\t");
            for (x = 0; x < BOARD_SIZE_X; ++x) {

                if ((x == 0) && (y % 2))
                    printf("    ");

                if (board[x][y] == 0)
                    printf("        ");
                else
                    printf(" \\___/  ");
            }
            printf("\n");
        }
    }
}

void boardRandom() {
    int i, j;
    srand(time(NULL));
    for (i = 0; i < BOARD_SIZE_Y; i++) {
        for (j = 0; j < BOARD_SIZE_X; ++j) {
            board[j][i] = rand() % 4;
        }
    }
}

void boardLoad(void *filename){
    int x, y, fillx, filly;
    char temp;
    char Directory[64];

    if(sys == WINDOWS) strcpy(Directory, "./");
    else strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");

    strcat(Directory, filename);
    input = fopen(Directory, "r");
    if (input == NULL) {
        printf("Error");
        return;
    }
    x = 0;
    y = 0;
    fillx = 0;
    filly = 0;
    //ignores score in file reading
    while(temp != ';'){
        fscanf(input, "%c", &temp);
    }
    fscanf(input, "%c", &temp);

    while(fscanf(input, "%c", &temp) != EOF){
        if(temp == ',') continue;
        if(temp == ';'){
            y++;
            x = 0;
            fscanf(input, "%c", &temp);
            while(fillx < BOARD_SIZE_X){
                board[fillx][y] = 0;
                fillx++;
            }
            fillx = 0;
            filly++;
            continue;
        }
        board[x][y] = (temp - '0');
        x++;
        fillx++;
    }
    fillx = 0;
    while(filly < BOARD_SIZE_Y){
        while(fillx < BOARD_SIZE_X){
            board[fillx][filly] = 0;
            fillx++;
        }
        fillx = 0;
        filly++;
    }
    fclose(input);
}
void boardOut(void *filename){
    int x, y, scP;
    char Directory[64];

    if(sys == WINDOWS) strcpy(Directory, "./");
    else strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    strcat(Directory, filename);
    output = fopen(Directory, "w");
    if (output == NULL) {
        printf("Error");
        return;
    }

    //print player scores
    for(scP = 0; scP < NR_OF_PLAYERS; scP++){
        fprintf(output, "%d", score[scP]);
        if(scP + 1 != NR_OF_PLAYERS) fprintf(output, ",");
        else fprintf(output, ";");
    }
    fprintf(output, "\n");
    // print board

    for(y = 0; y < BOARD_SIZE_Y; y++){
        for(x = 0; x < BOARD_SIZE_X; x++){
            fprintf(output, "%d", board[x][y]);
            if(x + 1 != BOARD_SIZE_X) fprintf(output, ",");
            else fprintf(output, ";");
        }
        fprintf(output, "\n");
    }
    fclose(input);
}
