#include <string.h>
#include <time.h>

#include "Phase_Loop.h"
#include "FileHandler.h"
#include "Define.h"
#include "System.h"


void scoreLoad(char *filename){
    FILE *input;
    int player;
    int temp, i;
    char tmp;
    char Directory[128];

    #ifdef _WIN32
    strcpy(Directory, "./");
    #else
    strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    #endif

    strcat(Directory, filename);
    input = fopen(Directory, "r");
    if(input == NULL){
        printf("There's no file with this name. Scores initialized with 0's\n");
        for(i = 0; i < nrOfPlayers; i++){
            score[i] = 0;
        }
    }
    player = 0;
    fscanf(input, "%d", &temp);
    fscanf(input, "%c", &tmp);
    do{
        fscanf(input, "%d", &temp);
        score[player] = temp;
        player++;
        fscanf(input, "%c", &tmp);
    }while(tmp != ';');
    fclose(input);
}

void scoreAdd(int player, int amount){
    score[player - 1] += amount;
}

void scorePrint(){
    int i;
    printf("\nSCORES:\n");
    for(i = 0; i < nrOfPlayers; i++){
        printf("|   P%d: %d   |", i+1, score[i]);
    }
    printf("\n\n");
}


void boardPrint() {
    int x, y;

    //Prints column's numbers
    printf("\t");
    for (x = 0; x < BoardMX; x++) {
        if (x < 10)
            printf("   %d   %d", x, x);
        if (x >= 10)
            printf("  %d  %d", x, x);
    }
    printf("\n\n");

    for (y = 0; y < BoardMY; y++) {

            printf("\t");
            for (x = 0; x < BoardMX; ++x) {

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


            for (x = 0; x < BoardMX; ++x) {

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
            for (x = 0; x < BoardMX; ++x) {

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

void boardRandom() {
    int i, j;
    srand(time(NULL));
    for (i = 0; i < BoardMY; i++) {
        for (j = 0; j < BoardMX; ++j) {
            board[j][i] = rand() % 4;
        }
    }
}

void boardLoad(char *filename){
    FILE *input;
    int x, y;
    char temp;
    char Directory[128];

    #ifdef _WIN32
    strcpy(Directory, "./");
    #else
    strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    #endif

    strcat(Directory, filename);
    input = fopen(Directory, "r");
    if (input == NULL) {
        boardRandom();
        return;
    }
    x = 0;
    y = 0;
    //ignores scores and current turn in file reading
    while(temp != ';'){
        fscanf(input, "%c", &temp);
    }
    fscanf(input, "%c", &temp);

    while(fscanf(input, "%d", &(board[x][y])) > 0){
        fscanf(input, "%c", &temp);
        while(temp != ';'){
            fscanf(input, "%d", &(board[++x][y]));
            fscanf(input, "%c", &temp);
        }
        while(x < BoardMX - 1){
            board[++x][y] = 0;
        }
        x = 0;
        y++;
        fscanf(input, "%c", &temp); // ignore new line character and clear ';' from temp
    }
    fclose(input);
}
void boardOut(char *filename){
    FILE *output;
    int x, y, i;
    char Directory[128];

    #ifdef _WIN32
    strcpy(Directory, "./");
    #else
    strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    #endif

    strcat(Directory, filename);
    output = fopen(Directory, "w");
    if (output == NULL) {
        printf("Output Error");
        return;
    }
    fprintf(output, "%d,", ((turn % nrOfPlayers) + 1));
    //print player scores
    for(i = 0; i < nrOfPlayers; i++){
        fprintf(output, "%d", score[i]);
        if(i + 1 != nrOfPlayers) fprintf(output, ",");
        else fprintf(output, ";");
    }
    fprintf(output, "\n");
    // print board

    for(y = 0; y < BoardMY; y++){
        for(x = 0; x < BoardMX; x++){
            fprintf(output, "%d", board[x][y]);
            if(x + 1 != BoardMX) fprintf(output, ",");
            else fprintf(output, ";");
        }
        fprintf(output, "\n");
    }
    fclose(output);
}

void setPlayers(char *filename){
    FILE *input;
    char Directory[128];
    int players = 0, tmp;
    char temp;

    #ifdef _WIN32
    strcpy(Directory, "./");
    #else
    strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    #endif

    strcat(Directory, filename);
    input = fopen(Directory, "r");

    if (input == NULL) {
        printf("Wrong input directory\n");
        return;
    }

    fscanf(input, "%d", &tmp);
    turn = tmp - 1;
    printf("turn: %d", turn);
    fscanf(input, "%c", &temp);
    while(temp != ';'){
        fscanf(input, "%d", &tmp);
        fscanf(input, "%c", &temp);
        players++;
    }
    nrOfPlayers = players;
    fclose(input);
}

void getBoardSize(char *filename){
    FILE *input;
    char Directory[128];
    int maxX = 0, maxY = 0, x = 1, itemp;
    char temp;

    #ifdef _WIN32
    strcpy(Directory, "./");
    #else
    strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    #endif

    strcat(Directory, filename);
    input = fopen(Directory, "r");

    //ignores scores and current turn in file reading
    while(temp != ';'){
        fscanf(input, "%c", &temp);
    }
    fscanf(input, "%c", &temp); // new line symbol

    while(fscanf(input, "%d", &itemp) > 0){
        while(fscanf(input, "%c", &temp) && temp != ';'){
            fscanf(input, "%d", &itemp);
            x++;
        }
        if(x > maxX) maxX = x;
        x = 1;
        maxY++;
    }
    BoardMX = maxX;
    BoardMY = maxY;
    fclose(input);
}
