#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define GAUCHE 1
#define HAUT 2
#define DROITE 4
#define BAS 8


typedef struct{
    int x;
    int y;
} Player;


typedef struct{
    int value;
    int walls;
} Case;




void displayBoard(Case** board, int* P_row, int* P_col){
	// Affiche le jeu ligne par ligne en fonction du tableau

    for (int i = 0; i < (*P_row); i++){

        // Cela va afficher les lignes horrizontales du jeu
        for (int j = 0; j < (*P_col); j++){
        	printf("+");
            // Trouver sur internet, cela permet de vérifier si le 2ème bit de la variable est à 1 ou 0, pour savoir s'il y a un mur à afficher.
            // Ca commence à 0, donc le bit 1 est celui à la deuxième place
            // Ici, c'est pour savoir s'il y a un mur en haut de la case
            if ((board[i][j].walls & (1 << 1)) != 0){
        		printf("----");
        	}
            // Pour afficher les murs en bas d'une case, on regarde la case d'au dessus et on affiche le mur de la case au dessus
            // Il faut pas que le i soit négatif, et cela ne pose pas de problème car il ne peux pas avoir de mus en bas de la première ligne
            else if (i != 0){
                if ((board[i - 1][j].walls & (1 << 3)) != 0){
                    printf("----");
                }
                else{
        		    printf("    ");
        	    }
            }
        	else{
        		printf("    ");
        	}
        }
        printf("+\n");

        // Maintenant on va afficher les murs verticaux et le contenu des cases
        for(int j=0; j<(*P_col); j++){
        	
            // Pour les murs à gauche d'une case
        	if((board[i][j].walls & (1 << 0)) != 0){
        		printf("|");
        	}
            // Même principe que pour les murs en bas des cases, ici à droite
            else if (j != 0){
                if ((board[i][j - 1].walls & (1 << 2)) != 0){
                    printf("|");
                }
                else{
        		    printf(" ");
        	    }
            }
        	else{
        		printf(" ");
        	}
        	
            // Maintenant on affiche le contenu
            if(board[i][j].value == 20){
                printf("\033[41m R1 \033[0m");
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
        }
        // Pour afficher le mur le plus à droite de la ligne, normalement pas besoin de if, mais on vérifie que le mur de la case a la bonne valeur
        if((board[i][*P_col - 1].walls & (1 << 2)) != 0){
    		printf("|");
        }
        printf("\n");
    }
    // La boucle au dessus ne va pas à la toute dernière ligne
    // Donc on affiche la dernière ligne ici
    for (int j = 0; j < (*P_col); j++){
        printf("+");
        if ((board[*P_row - 1][j].walls & (1 << 3)) != 0){
    		printf("----");
    	}
        else{
            printf("    ");
        }
    }
    printf("+\n");
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






int mursAutorise(Case** board, int* P_row, int* P_col, int mur_haut, int mur_bas, int mur_gauche, int mur_droite){
    // On regarde les cases à côtés pour qu'il n'y est pas 2 murs côte à côte ou qui se superposent
    for (int a = -1; a < 2; a++){
        if ( ((board[0][mur_haut + a].walls & (1 << 0)) != 0) || ((board[*P_row - 1][mur_bas + a].walls & (1 << 0)) != 0)){
            return 0;
        }
        else if ( ((board[mur_gauche + a][0].walls & (1 << 1)) != 0) || ((board[mur_droite + a][*P_col - 1].walls & (1 << 1)) != 0)){
            return 0;
        }
    }
    return 1;
}


// Cette fonction créé les murs sur les cotés du cadrillage
void mursBords(Case** board, int* P_row, int* P_col){
	for (int i = 0 ; i < *P_row; i++){
		board[i][0].walls += GAUCHE; // Création des mur au bord de gauche
       	board[i][*P_col-1].walls += DROITE; // Création des murs au bord de droite
	}
    for (int j = 0; j < *P_col; j++){
        board[0][j].walls += HAUT;  // Création des mur au bord en haut
        board[*P_row - 1][j].walls += BAS; // Création des murs au bord en bas
    }

    // On créé les 2 murs parallèles sur chaque bords
    int i = 0;
    while(i < 2){
        int mur_haut = rand() % (*P_col - 4) + 2;
        int mur_bas = rand() % (*P_col - 4) + 2;
        int mur_gauche = rand() % (*P_row - 4) + 2;
        int mur_droite = rand() % (*P_row - 4) + 2;

        // Si il n'y a pas déjà un mur là où on veut le placer ou à côté
        if(mursAutorise(board, P_row, P_col, mur_haut, mur_bas, mur_gauche, mur_droite) == 1){
            board[0][mur_haut].walls += GAUCHE;
            board[*P_row - 1][mur_bas].walls += GAUCHE;
            board[mur_gauche][0].walls += HAUT;
            board[mur_droite][*P_col - 1].walls += HAUT;
            i++;
        }
    }
}






void mursCibles(Case** board, int i, int j){
    int mur = rand() % 4;
    // On initialise les valeurs des murs de la cible rentré
    // Les murs ont ces valeurs là pour que l'on puisse par la suite utiliser les bits remplis pour savoir s'il y a un mur
    switch(mur){
        case 0 :
            board[i][j].walls = GAUCHE + HAUT;
            break;
        case 1 :
            board[i][j].walls = HAUT + DROITE;
            break;
        case 2 :
            board[i][j].walls = DROITE + BAS;
            break;
        case 3 :
            board[i][j].walls = BAS + GAUCHE;
            break; 
    }
}


int cibleAutorise(Case** board, int i, int j){
    // On parcours les cases autour de la case rentrer en paramètre pour pas mettre 2 cibles côte à côte
    for (int a = -1; a < 2; a++){
        for (int b = -1; b < 2; b++){
            // On regarde si une case autour possède 2 murs, c'est à dire soit une cible, soit les murs perpendiculaires sur les bords
            // Pour ne pas mettre une cible à côté
            if ((board[i + a][j + b].walls == (DROITE + BAS)) ||
            (board[i + a][j + b].walls == (BAS + GAUCHE)) ||
            (board[i + a][j + b].walls == (GAUCHE + HAUT)) ||
            (board[i + a][j + b].walls == (HAUT + DROITE))){
                return 0;
            }
        }
    }
    return 1;
}

void creerCibles(Case** board, int* P_row, int* P_col){
    int nb_cibles = 0;
    // On boucle tant que toutes les cibles ne sont pas placées
    while(nb_cibles < 18){
        // On prend une case aléatoire du tableau
        int i = rand() % (*P_row - 3) + 1;
        int j = rand() % (*P_col - 3) + 1;
        // On vérifie que la cible est sur une bonne case
        if(cibleAutorise(board, i, j) == 1){
            // La valeur de la case est le numéro de la cible
            board[i][j].value = nb_cibles + 1;
            // On créer les murs autour de la cible
            mursCibles(board, i, j);
            nb_cibles ++;
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
    printf("\033[H\033[2J");
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

    mursBords(board, P_row, P_col);
    creerCibles(board, P_row, P_col);
    creerRobots(board, P_row, P_col, R);

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
