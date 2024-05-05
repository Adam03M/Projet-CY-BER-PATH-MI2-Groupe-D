#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct{
    int x;
    int y;
} Player;


typedef struct{
    int value;
    int walls;
} Case;


void displayTabBoard(Case** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
            printf("%d ", board[i][j].value);
        }
        printf("\n");
    }
}



void displayBoard(Case** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
            printf("+----");
        }
        printf("+ \n");
        for(int j=0; j<(*P_col); j++){
            if(board[i][j].value == 20){
                printf("| P1 ");
            }
            else if(board[i][j].value < 10 && board[i][j].value > 0){
                printf("| %d  ", board[i][j].value);
            }
            else if(board[i][j].value >= 10){
                printf("| %d ", board[i][j].value);
            }
            else{
                printf("|    ");
            }
        }
        printf("| \n");
    }
    for(int j=0; j<(*P_col); j++){
        printf("+----");
    }
    printf("+ \n");
}




void mursCibles(Case** board, int i, int j){
    int mur = rand() % 4;
    if(mur == 0){
        board[i][j].walls = 3;
    }
    else if(mur == 1){
        board[i][j].walls = 6;
    }
    else if(mur == 1){
        board[i][j].walls = 12;
    }
    else{
        board[i][j].walls = 9;
    }
}

int cibleAutorise(Case** board, int i, int j){
    for(int a=-1; a<2; a++){
        for(int b=-1; b<2; b++){
            if((board[i + a][j + b].value != 0) && (i != 0 || j != 0)){
                return 0;
            }
        }
    }
    return 1;
}

void creerCibles(Case** board, int* P_row, int* P_col){
    int nb_cibles = 0;
    int aleatoire;
    while(nb_cibles < 18){
        for(int i=1; i < (*P_row) - 1; i++){
            for(int j=1; j < (*P_col) - 1; j++){
                aleatoire = rand() % 40;
                if(aleatoire == 1 && cibleAutorise(board, i, j) == 1){
                    board[i][j].value = nb_cibles + 1;
                    mursCibles(board, i, j);
                    nb_cibles ++;
                }
                if(nb_cibles >= 18){
                    break;
                }
            }
            if(nb_cibles >= 18){
                break;
            }
        }
    }
}





void initBoard(Case** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
            board[i][j].value = 0;
            board[i][j].walls = 0;
        }
    }
}


Case** createBoard(int* P_row, int* P_col){
    *P_row = rand() % 5 + 15;
    *P_col = rand() % 5 + 15;
    printf("row : %d et col : %d\n", *P_row, *P_col);

    Case** board = malloc(sizeof(*board) * (*P_row));

    for(int i = 0; i < (*P_row); i++){
        board[i] = malloc(sizeof(**board) * (*P_col));
    }
    if(board == NULL){
        printf("L'allocation de la mémoire pour créer le plateau a échouée.\n");
        exit(1);
    }

    initBoard(board, P_row, P_col);

    return board;
}


int move(Case** board, int* P_row, int* P_col, Player* P1){
    char userInput;
    printf("Entrez les touches \"z\" \"q\" \"s\" ou \"d\" pour pour vous déplacer, entrez \"l\" pour quitter le jeu.\n");
    fflush(stdin);
    scanf("%c", &userInput);

    switch(userInput){
        case 'z' :
            board[(*P1).y][(*P1).x].value = 0;
            if((*P1).y - 1 >= 0){
                (*P1).y -= 1;
            }
            break;
        case 'q' :
            board[(*P1).y][(*P1).x].value = 0;
            if((*P1).x - 1 >= 0){
                (*P1).x -= 1;
            }
            break;
        case 's' :
            board[(*P1).y][(*P1).x].value = 0;
            if((*P1).y + 1 < *P_row){
                (*P1).y += 1;
            }
            break;
        case 'd' :
            board[(*P1).y][(*P1).x].value = 0;
            if((*P1).x + 1< *P_col){
                (*P1).x += 1;
            }
            break;
        case 'l' :
            return -1;
        default :
            return 0;
    }
    board[(*P1).y][(*P1).x].value = 20;
    displayTabBoard(board, P_row, P_col);
    displayBoard(board, P_row, P_col);
    return 1;
}


int main(){
    srand(time(NULL));
    int row = 0;
    int col = 0;

    int* P_row = &row;
    int* P_col = &col;

    Case** board = createBoard(P_row, P_col);

    Player P1; 

    P1.x = 0;
    P1.y = *P_row - 1;

    board[P1.y][P1.x].value = 20;

    creerCibles(board, P_row, P_col);

    displayTabBoard(board, P_row, P_col);

    displayBoard(board, P_row, P_col);

    do{
        int result = 0;
        result = move(board, P_row, P_col, &P1);
        if(result == -1){
            break;
        }
    } while(1);

    for(int i=0; i < (*P_row); i++){
        free(board[i]);
    }
    free(board);

    printf("Fini");

    return 0;
}