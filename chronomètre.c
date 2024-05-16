#include <stdio.h>
#include <time.h>

int main(void) {
    printf("Vous avez 30 secondes pour réfléchir\n");
    int seconds = 30;
    for(int i=seconds;i>=11;i--){
        
        printf("\n%02d", seconds); //Affiches des seconds avec un zéro pour chaque dizaines
        fflush(stdout);//Cette fonction garanti que l'affichage des seconde a bien lieu
        clock_t stop = clock() + CLOCKS_PER_SEC;// Calcul a quel moment la boucle doit s'arrêter
        while(clock()< stop){}// Boucle qui permet de s'arrêter au moment ou l'instant voulu est atteint
        seconds--; // Décrémente les secondes jusqu'a zéro
        if(seconds<=10){ //Boucles des 10 dernière secondes
            for(int j=seconds;j>=0;j--){
                printf("\033[0;31m"); //Affiche le texte en rouge
                printf("\n%02d", seconds); // Affiches des secondes avec un zéro pour chaque dizaines
                fflush(stdout);
                clock_t stop = clock() + CLOCKS_PER_SEC;
                while(clock()< stop){}
                seconds--;
                
                
            }
            
            printf("\033[0m"); //On réinitialise les couleurs
        }

        
    }
    
    printf("\n");
    printf("Temps écoulé!"); //Message qui prévient le joueur de la fin du temps règlementaire
    
    return 0;
}
