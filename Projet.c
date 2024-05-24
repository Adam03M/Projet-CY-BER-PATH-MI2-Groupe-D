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

void SideWalls(Case** board, int* P_row, int* P_col){
    
    for(int i=0;i<*(P_row);i++){
        for(int j=0;j<*(P_col);j++){
            if(i==0 || i==*(P_row-1) || j==0 || j == *(P_col -1)){
                board[i][j].walls = rand()%2;
                
            }
            else{
                
                board[i][j].walls = 0;
                
            }
            
        }
                
    }
    
}

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
            if(board[i][j].value == 0){
                printf("|    ");
            }
            else if(board[i][j].value == 20){
                printf("| P1 ");
            }
            else if(board[i][j].value == 5){
                printf("| 5  ");
            }
        }
        printf("| \n");
    }
    for(int j=0; j<(*P_col); j++){
        printf("+----");
    }
    printf("+ \n");
}



void createWalls(Case** board, int* P_row, int* P_col){
    // Donnez des valeurs aux cases qui auront des murs.
}


void initBoard(Case** board, int* P_row, int* P_col){
    for(int i=0; i<(*P_row); i++){
        for(int j=0; j<(*P_col); j++){
            board[i][j].value = 0;
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
	 int* Nombre_de_joueurs(int*nb_de_joueurs){
	      printf("Donnez le nombre de joueurs \n");
	      scanf("%d",&(*nb_de_joueurs));
	      return nb_de_joueurs;
	  }
	  
	  
	  int* Nombre_de_mouvement(int*nb_de_joueurs, int*nbrmvmt){
	      int i=0;
	      nbrmvmt=malloc((*nb_de_joueurs)*sizeof(int));
	      	if (nbrmvmt == NULL)
		  {
			printf("L'allocation de la mémoire pour le nombre de mouvement a échouée .\n");
			exit (5);
		  }
	      while(i< (*nb_de_joueurs)){
	          
	          printf("Donnez le nombre de mouvements nécessaires \n");
	     	  scanf("%d",&nbrmvmt[i]);
		    while(nbrmvmt[i]<= 0){
			  printf("donnez un autre nombre  \n");
			  scanf("%d",&nbrmvmt[i]);
	    	    }
	          i++;
	      }
		 int min = nbrmvmt[0];  
		 for(int j= 0;j<(*nb_de_joueurs),j++){
			 if(nbrmvmt[j]<min){
				 min =nbrmvmt[j]
					 }
		 }


			 
		return nbrmvmt;
	  }

	int Joueur_commence(int *nb_de_joueurs,int*nbrmvmt){
	 Nombre_de_joueurs(nb_de_joueurs);
	 Nombre_de_mouvement(nb_de_joueurs,nbrmvmt);

	int i=0;
	int min = nbrmvmt[0];  
		 for(i= 0;i<(*nb_de_joueurs),i++){
			 if(nbrmvmt[i]<min){
				 min =nbrmvmt[i];
			 }
		 }
	return min;
	}
//on appelle la foncion joueur commence dans le main et ensuite :
//printf("celui qui a donnez %d comme nombre de mouvement commence",min);
	
int Attri_de_points( int nb_deplacement; in* nb_mvt, int* score, int joueur, int nb_de_joueurs){
    
        if(nb_deplacement>nb_mvt[joueur]){
            for(int i=0; i<nb_de_joueurs,i++){
                if(i!= joueur){
                    score[i]++;
                }
            }
            
            
        }
        else if(nb_deplacement == nb_mvt[joueur]){
            
        }
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

    createWalls(board, P_row, P_col);

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
