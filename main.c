#include "fonctions.h"


int main(void){
    srand(time(NULL));
    
    int nb_de_joueurs = nbDeJoueurs();
    // Créé le tableau des scores en fonction du nombre de joueurs de la partie
    int* score = calloc( nb_de_joueurs, sizeof(int)); // Met le tableau à 0
    
    if(score == NULL){
        printf("L'allocation de la mémoire pour le tableau des scores a échouée.\n");
        exit(1);
    }

    int resultat = 1;
    int nb_de_manches = 4;
    int max = 0;
    int i_max = 0;
    
    
    for(int i = 1; i < nb_de_manches + 1; i++){
        // On lance une manche du jeu
        printf("La prochaine manche commence dans 15 secondes.\n");
        printf("C'est la %de manche.\n", i);
        chronometre(15);
        resultat = manche(score, nb_de_joueurs);
        // Si tous les joueurs on estimés que la cible était inatteignable, on relance une manche sans la compter
        if (resultat == -1 || resultat == 0){
            i--;
        }
    }
    
    // On affiche le joueur gagnant
    for(int i = 0; i < nb_de_joueurs; i++){
        if(score[i] > max){
            max = score[i];
            i_max = i;
        }
    }
    printf("C'est le joueur %d qui a gagné cette partie !\n", i_max+1);
    
    free(score);
    
    printf("Merci d'avoir joué !\n");

    return 0;
}
