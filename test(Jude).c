#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Le programme va choisir un robot
Player* ChooseBot(Case** board, int* P_row, int* P_col){

		Player* a = creerRobots(board, P_row, P_col);
		int i = rand()%4;


	return a[i];
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


// Cette fonction créee les murs sur les cotés du cadrillage
 void SideWalls(Case** board, int* P_row, int* P_col){
    
    for(int i=0;i<*P_row;i++){
        for(int j=0;j<*P_col;j++){
            if(i==0 || i==*(P_row-1) || j==0 || j == *(P_col -1) ){
                board[0][j].walls = rand()%2;  // Création des mur perpendiculaire a gauche
                board[i][0].walls = rand()%2; // Création des mur perpendiculaire en haut
                board[i][*P_col-1].walls= rand()%2; // Création des murs perpendiculaires à droite
                board[*P_row-1][j].walls= rand()%2; // Création des murs perpendiculaires à gauche
            }
            else{
                
                board[i][j].walls = 0;
                
            }
            
        }
        
        
    }
    
}
