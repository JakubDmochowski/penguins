#include "FileHandler.h"

#define MAC

void scoreLoad(void *filename){
    int player;
    int temp[1];
    char tmp[1];
    char Directory[64];
    #ifdef MAC
        strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    #else WINDOWS
        strcpy(Directory, "./");
    #endif // MAC
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
        printf("|\tP%d: %d\t|", i, score[i]);
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
        for (j = 0; j < BOARD_SIZE_X; j++) {
            board[j][i] = rand() % 6;
        }
    }
}


void boardLoad(void *filename){
    int i, j;
    char temp;
    char Directory[64];
    #ifdef MAC
        strcpy(Directory, "/Users/emildzwonek/Documents/Studia/EPFU/Penguins/app/");
    #else WINDOWS
        strcpy(Directory, "./");
    #endif // MAC
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
            j++;
            i = 0;
            fscanf(input, "%c", &temp);
            continue;
        }
        board[i][j] = (temp - '0');
        i++;
    }
    fclose(input);
}
