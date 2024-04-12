#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void displayTabBoard(int** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
            printf("[%d] ", board[i][j]);
        }
        printf("\n");
    }
}

void displayBoard(int** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_col); i++){
        printf(" ____");
    }
    printf("\n");
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col) + 1; j++){
            printf("|    ");
        }
        printf("\n");
        for(int j=0; j<(*P_col); j++){
            printf("|____");
            if(j == (*P_col) - 1){
                printf("|   ");
            }
        }
        printf("\n");
    }
    
}


void initBoard(int** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
            board[i][j] = 0;
        }
    }
}


int** createBoard(int* P_row, int* P_col){
    *P_row = rand() % 5 + 15;
    *P_col = rand() % 5 + 15;
    printf("row : %d et col : %d\n", *P_row, *P_col);

    int ** board = malloc(sizeof(int*) * (*P_row));

    for(int i=0; i < (*P_row); i++){
        board[i] = malloc(sizeof(int) * (*P_col));
    }
    if(board == NULL){
        printf("L'allocation de la m�moire pour cr�er le plateau � �chou�e.");
        exit(1);
    }

    initBoard(board, P_row, P_col);

    return board;
}


int main(){
    srand(time(NULL));

    int row = 0;
    int col = 0;

    int* P_row = &row;
    int* P_col = &col;

    int** board = createBoard(P_row, P_col);

    displayTabBoard(board, P_row, P_col);

    displayBoard(board, P_row, P_col);

    for(int i=0; i < (*P_row); i++){
        free(board[i]);
    }
    free(board);

    return 0;
}