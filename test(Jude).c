#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    int x;
    int y;
    
} Cible;


void Cadrillage(int** tab,int col, int line){
    
    tab =  malloc(sizeof(int)*line);
    
    if(tab == NULL){
        
        exit(1);
        
    }
    for(int i=0;i<line;i++){
        
        tab[i] = malloc(sizeof(int)*col);
        
    }
    for(int k=0;k<line;k++){
        
        for(int j=0;j<col;j++){
            tab[k][j] = 0;
            printf("|_");
        }
        printf("|\n");
        
    }
}

int afficherCible(){
   
    if(){
        
    }
    
    
    return 0;
}




int main(){
    srand(time(NULL));
    int a = rand()%6+15;
    int b = rand()%6+15;
    
    Cadrillage(a,b);
    

    return 0;
}
