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


// Affiche les nombres du tableau pour voir comment il est rempli
void displayTabBoard(Case** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
            printf("%d ", board[i][j].value);
        }
        printf("\n");
    }
}



void displayBoard(Case** board, int* P_row, int* P_col){
	// Affiche le jeu ligne par ligne en fonction du tableau
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
        	printf("+");
        	if((board[i][j].walls & 2) != 0 || (board[i][j].walls & 4) != 0){
        		printf("----");
        	}
        	else{
        		printf("    ");
        	}
        }
        printf("+\n");
        for(int j=0; j<(*P_col); j++){
        	
        	if(board[i][j].walls&1 != 0){
        		printf("|");
        	}
        	else{
        		printf(" ");
        	}
        	
            if(board[i][j].value >= 20){
                printf(" 🤖 ");
            }
            else if(board[i][j].value < 10 && board[i][j].value > 0){
                printf(" %d  ", board[i][j].value);
            }
            else if(board[i][j].value >= 10 && board[i][j].value <= 18){
                printf(" %d ", board[i][j].value);
            }
            else{
                printf("    ");
            }
            
            if(board[i][j].walls&3 != 0){
        		printf("|");
        	}
        	else{
        		printf(" ");
        	}
        }
        printf("\n");
    }
}






// Cette fonction verifie si il y'a un mur et empêche le joueur d'avancer si tel est le cas
void PlayerWalls(Case** board, int* P_row, int* P_col,Player*P1){
    for(int i=0;i<*(P_row);i++){ // Parcours des lignes
        for(int j=0;j<*(P_col);j++){ // Parcours des colonnes
            if(board[i][j].walls==1){ // Vérification de la présence du mur
                printf("Vous ne pouvez pas avancer, il y'a un mur!"); // Message d'erreur
            }
            else{
                printf("P1"); // Le joueur est autorisé à avancer
            }
        }
    }
}




// Cette fonction créé les murs sur les cotés du cadrillage
void mursCotes(Case** board, int* P_row, int* P_col){
	for(int i=0;i<*P_row;i++){
		board[i][0].walls += 1; // Création des mur perpendiculaire à gauche
       	board[i][*P_col-1].walls += 4; // Création des murs perpendiculaires à droite
	}
    for(int j=0;j<*P_col;j++){
        board[0][j].walls += 2;  // Création des mur perpendiculaire en haut
        board[*P_row-1][j].walls += 8; // Création des murs perpendiculaires en bas
    }
    printf("Le 0 0 est à : %d\n", board[0][0].walls);
}






void mursCibles(Case** board, int i, int j){
    int mur = rand() % 4;
    // On initialise les valeurs des murs de la cible rentré
    // Les murs ont ces valeurs là pour que l'on puisse par la suite utiliser les bits remplis pour savoir s'il y a un mur
    switch(mur){
        case 0 :
            board[i][j].walls = 1 + 2;
            break;
        case 1 :
            board[i][j].walls = 2 + 4;
            break;
        case 2 :
            board[i][j].walls = 4 + 8;
            break;
        case 3 :
            board[i][j].walls = 8 + 1;
            break;
    }
}


int cibleAutorise(Case** board, int i, int j){
    // On parcours les cases autour de la case rentrer en paramètre pour pas mettre 2 cibles côte à côte
    for(int a=-1; a<2; a++){
        for(int b=-1; b<2; b++){
            if(board[i + a][j + b].value != 0){
                return 0;
            }
        }
    }
    return 1;
}

void creerCibles(Case** board, int* P_row, int* P_col){
    int nb_cibles = 0;
    int aleatoire;
    // On boucle tant que toutes les cibles ne sont pas placées
    while(nb_cibles < 18){
        for(int i=1; i < (*P_row) - 1; i++){
            for(int j=1; j < (*P_col) - 1; j++){
                // On met un grand nombre aléatoire pour que les numéros des cibles soient bien espacés et donc mélangés dans le tableau
                aleatoire = rand() % 50;
                // On vérifie que la cible est une bonne case
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




void creerRobots(Case** board, int* P_row, int* P_col, Player* R){
    int i = 0;

    while(i < 4){
        R[i].x = rand() % (*P_col);
        R[i].y = rand() % (*P_row);
        // Si la case est vide
        if(board[R[i].y][R[i].x].value == 0){
            // Place un joueur
            board[R[i].y][R[i].x].value = i + 20;
            i++;
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
    board[(*P1).y][(*P1).x].value = 30;
    displayTabBoard(board, P_row, P_col);
    displayBoard(board, P_row, P_col);
    return 1;
}


int main(){
    srand(time(NULL));
    int row = 0;
    int col = 0;
    int nb_joueurs = 0;

    int* P_row = &row;
    int* P_col = &col;
    int* P_nb_joueurs = &nb_joueurs;
        
    // Creation du tableau de joueurs
    Player R[4];

    Case** board = createBoard(P_row, P_col);

    Player P1; 

    P1.x = 0;
    P1.y = *P_row - 1;

    board[P1.y][P1.x].value = 30;

    creerCibles(board, P_row, P_col);
    creerRobots(board, P_row, P_col, R);
    mursCotes(board, P_row, P_col);

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
