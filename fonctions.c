#include "fonctions.h"
#include "couleurs.h"

// Code trouver dans le cours pour ces 2 fonctions
// Permet d'utiliser scanf sans problèmes avec ce que l'utilisateur rentre
int scanf_int(char* message){
    int verif = 0;
    int valeur = 1;
    while (verif != 1 || valeur < 0){   
        printf("%s", message);
        verif = scanf("%d", &valeur);
        while(getchar() != '\n'){}
    }
    return valeur;
}

char scanf_char(char* message){
    int verif = 0;
    char valeur = 1;
    while (verif != 1 || valeur < 0){   
        printf("%s", message);
        verif = scanf("%c", &valeur);
        while(getchar()!='\n'){}
    }
    return valeur;
}


void afficheJeu(Case** tab_jeu, int* P_ligne, int* P_col){
	// Affiche le jeu ligne par ligne en fonction du tableau

    for (int i = 0; i < (*P_ligne); i++){

        // Cela va afficher les lignes horrizontales du jeu
        for (int j = 0; j < (*P_col); j++){
        	printf("+");
            // Trouver sur internet, cela permet de vérifier si le 2ème bit de la variable est à 1 ou 0, pour savoir s'il y a un mur à afficher.
            // Ca commence à 0, donc le bit 1 est celui à la deuxième place
            // Ici, c'est pour savoir s'il y a un mur en haut de la case
            if ((tab_jeu[i][j].murs & (1 << 1)) != 0){
        		printf("----");
        	}
            // Pour afficher les murs en bas d'une case, on regarde la case d'au dessus et on affiche le mur de la case au dessus
            // Il faut pas que le i soit négatif, et cela ne pose pas de problème car il ne peux pas avoir de mus en bas de la première ligne
            else if (i != 0){
                if ((tab_jeu[i - 1][j].murs & (1 << 3)) != 0){
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
        	if((tab_jeu[i][j].murs & (1 << 0)) != 0){
        		printf("|");
        	}
            // Même principe que pour les murs en bas des cases, ici à droite
            else if (j != 0){
                if ((tab_jeu[i][j - 1].murs & (1 << 2)) != 0){
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
            if(tab_jeu[i][j].robot != 0){
                if(tab_jeu[i][j].robot == 1){
                    couleur("41");
                }
                else if(tab_jeu[i][j].robot == 2){
                    couleur("42");
                }
                else if(tab_jeu[i][j].robot == 3){
                    couleur("44");
                }
                else{
                    couleur("46");
                }
                
                printf(" 🤖 ");
                couleur("0");
            }
            else if(tab_jeu[i][j].valeur < 10 && tab_jeu[i][j].valeur > 0){
                printf(" %d  ", tab_jeu[i][j].valeur);
            }
            else if(tab_jeu[i][j].valeur >= 10 && tab_jeu[i][j].valeur <= 18){
                printf(" %d ", tab_jeu[i][j].valeur);
            }
            else{
                printf("    ");
            }
        }
        // Pour afficher le mur le plus à droite de la ligne, normalement pas besoin de if, mais on vérifie que le mur de la case a la bonne valeur
        if((tab_jeu[i][*P_col - 1].murs & (1 << 2)) != 0){
    		printf("|");
        }
        printf("\n");
    }
    // La boucle au dessus ne va pas à la toute dernière ligne
    // Donc on affiche la dernière ligne ici
    for (int j = 0; j < (*P_col); j++){
        printf("+");
        if ((tab_jeu[*P_ligne - 1][j].murs & (1 << 3)) != 0){
    		printf("----");
    	}
        else{
            printf("    ");
        }
    }
    printf("+\n");
}






// Cette fonction verifie si les murs en paramètres sont sur des cases autorisées
int mursAutorise(Case** tab_jeu, int* P_ligne, int* P_col, int mur_haut, int mur_bas, int mur_gauche, int mur_droite){
    // On regarde les cases à côtés pour qu'il n'y est pas 2 murs côte à côte ou qui se superposent
    for (int a = -1; a < 2; a++){
        if ( ((tab_jeu[0][mur_haut + a].murs & (1 << 0)) != 0) || ((tab_jeu[*P_ligne - 1][mur_bas + a].murs & (1 << 0)) != 0) ||
        ((tab_jeu[mur_gauche + a][0].murs & (1 << 1)) != 0) || ((tab_jeu[mur_droite + a][*P_col - 1].murs & (1 << 1)) != 0)){
            return 0;
        }
    }
    return 1;
}


// Cette fonction créée les 2 murs parallèles de chaque bords
void mursParalleles(Case** tab_jeu, int* P_ligne, int* P_col){
    int i = 0;
    while(i < 2){
        int mur_haut = rand() % (*P_col - 4) + 2;
        int mur_bas = rand() % (*P_col - 4) + 2;
        int mur_gauche = rand() % (*P_ligne - 4) + 2;
        int mur_droite = rand() % (*P_ligne - 4) + 2;

        // Si il n'y a pas déjà un mur là où on veut le placer ou à côté
        if(mursAutorise(tab_jeu, P_ligne, P_col, mur_haut, mur_bas, mur_gauche, mur_droite) == 1){
            tab_jeu[0][mur_haut].murs += GAUCHE;
            tab_jeu[*P_ligne - 1][mur_bas].murs += GAUCHE;
            tab_jeu[mur_gauche][0].murs += HAUT;
            tab_jeu[mur_droite][*P_col - 1].murs += HAUT;
            i++;
        }
    }
}


// Cette fonction créée les murs sur les cotés du plateau
void mursBords(Case** tab_jeu, int* P_ligne, int* P_col){
	for (int i = 0 ; i < *P_ligne; i++){
		tab_jeu[i][0].murs += GAUCHE; // Création des mur au bord de gauche
       	tab_jeu[i][*P_col - 1].murs += DROITE; // Création des murs au bord de droite
	}
    for (int j = 0; j < *P_col; j++){
        tab_jeu[0][j].murs += HAUT;  // Création des mur au bord en haut
        tab_jeu[*P_ligne - 1][j].murs += BAS; // Création des murs au bord en bas
    }
}






void mursCibles(Case** tab_jeu, int i, int j){
    int mur = rand() % 4;
    // On initialise les valeurs des murs de la cible rentré
    // Les murs ont ces valeurs là pour que l'on puisse par la suite utiliser les bits remplis pour savoir s'il y a un mur
    switch(mur){
        case 0 :
            tab_jeu[i][j].murs = GAUCHE + HAUT;
            break;
        case 1 :
            tab_jeu[i][j].murs = HAUT + DROITE;
            break;
        case 2 :
            tab_jeu[i][j].murs = DROITE + BAS;
            break;
        case 3 :
            tab_jeu[i][j].murs = BAS + GAUCHE;
            break; 
    }
}


int cibleAutorise(Case** tab_jeu, int i, int j){
    // On parcours les cases autour de la case rentrer en paramètre pour pas mettre 2 cibles côte à côte
    for (int a = -1; a < 2; a++){
        for (int b = -1; b < 2; b++){
            // On regarde si une case autour possède 2 murs, c'est à dire soit une cible, soit les murs perpendiculaires sur les bords
            // Pour ne pas mettre une cible à côté
            if ((tab_jeu[i + a][j + b].murs == (DROITE + BAS)) ||
            (tab_jeu[i + a][j + b].murs == (BAS + GAUCHE)) ||
            (tab_jeu[i + a][j + b].murs == (GAUCHE + HAUT)) ||
            (tab_jeu[i + a][j + b].murs == (HAUT + DROITE))){
                return 0;
            }
        }
    }
    return 1;
}

void creerCibles(Case** tab_jeu, int* P_ligne, int* P_col){
    int nb_cibles = 0;
    // On boucle tant que toutes les cibles ne sont pas placées
    while(nb_cibles < 18){
        // On prend une case aléatoire du tableau
        int i = rand() % (*P_ligne - 3) + 1;
        int j = rand() % (*P_col - 3) + 1;
        // On vérifie que la cible est sur une bonne case
        if(cibleAutorise(tab_jeu, i, j) == 1){
            // La valeur de la case est le numéro de la cible
            tab_jeu[i][j].valeur = nb_cibles + 1;
            // On créer les murs autour de la cible
            mursCibles(tab_jeu, i, j);
            nb_cibles ++;
        }
    }
}




void creerRobots(Case** tab_jeu, int* P_ligne, int* P_col){
    int i = 0;
    int x = 0;
    int y = 0;

    while(i < 4){
        x = rand() % (*P_col);
        y = rand() % (*P_ligne);
        // Si la case est vide
        if(tab_jeu[y][x].valeur == 0 && tab_jeu[y][x].robot == 0){
            // Place un joueur
            tab_jeu[y][x].robot = i + 1;
            i++;
        }
    }
}






void initCasesJeu(Case** tab_jeu, int* P_ligne, int* P_col){
    for(int i=0; i<(*P_ligne); i++){
        for(int j=0; j<(*P_col); j++){
            tab_jeu[i][j].valeur = 0;
            tab_jeu[i][j].murs = 0;
            tab_jeu[i][j].robot = 0;
        }
    }
}


Case** creerTabJeu(int* P_ligne, int* P_col){
    *P_ligne = rand() % 6 + 15;
    *P_col = rand() % 6 + 15;

    Case** tab_jeu = malloc(sizeof(*tab_jeu) * (*P_ligne));

    for(int i = 0; i < (*P_ligne); i++){
        tab_jeu[i] = malloc(sizeof(**tab_jeu) * (*P_col));
    }
    if(tab_jeu == NULL){
        printf("L'allocation de la mémoire pour créer le plateau a échouée.\n");
        exit(1);
    }

    initCasesJeu(tab_jeu, P_ligne, P_col);

    return tab_jeu;
}






// Cette fonction choisi une cible parmis les 18 
int ChoixCible(Case** tab_jeu, int* P_row, int* P_col){
	int cibleChoisie;
    int k = 0;

	do{
        cibleChoisie = rand() % 18 + 1;
        for(int i = 0; i < *(P_row); i++){ // Parcours des cases
            for(int j = 0; j < *(P_col); j++){
                // Trouve la cible choisi et vérifie que la case de la cible n'est pas occupée
                if(tab_jeu[i][j].valeur == cibleChoisie && tab_jeu[i][j].robot == 0){
                    return cibleChoisie; // Retour de la cible choisie par le programme
                }
            }
        }
        k++;
	} while(k < 20); // On répète l'opération tant que la case n'est pas choisi, où si cela prends trop d'essai, c'est qu'il y a un problème

    return -1;
}


// Le programme va choisir un robot
int ChoixRobot(Case** tab_jeu, int* P_row, int* P_col, int* coordXRobot, int* coordYRobot){
    int robotChoisi = rand() % 4 + 1; // La valeur en 1 et 4 pour choisir le robot

	for(int i = 0; i < *(P_row); i++){ // Parcours des cases
        for(int j = 0; j < *(P_col); j++){
            // Trouve le robot choisi
            if(tab_jeu[i][j].robot == robotChoisi){
                *coordXRobot = j;
                *coordYRobot = i;
                return robotChoisi; // Retour du robot choisi
            }
        }
    }
    return -1; // Le robot n'a pas été trouvé, il y a une erreur
}


void chronometre(int secondes){
    for(int i = secondes; i >= 11; i--){
        printf("%02d ", secondes); //Affiches des seconds avec un zéro pour chaque dizaines
        fflush(stdout); // Cette fonction garanti que l'affichage des seconde a bien lieu
        clock_t stop = clock() + CLOCKS_PER_SEC;// Calcul a quel moment la boucle doit s'arrêter
        while(clock() < stop){} // Boucle qui permet de s'arrêter au moment ou l'instant voulu est atteint
		secondes--; // Décrémente les secondes jusqu'a zéro
		if(secondes <= 10){ // Boucles des 10 dernière secondes
		    for(int j = secondes; j >= 0; j--){
		        couleur("31"); // Affiche le texte en rouge
		        printf("%02d ", secondes); // Affiches des secondes avec un zéro pour chaque dizaines
		        fflush(stdout);
		        clock_t stop = clock() + CLOCKS_PER_SEC;
		        while(clock() < stop){}
		        secondes--;
		   	}
			couleur("0"); // On réinitialise les couleurs
		}
    }
    printf("\n");
    printf("Temps écoulé !\n"); // Message qui prévient le joueur de la fin du temps règlementaire
}


int nbDeJoueurs(){
    int nb_de_joueurs = scanf_int("Donnez le nombre de joueurs pour cette partie. (minimum 2)\n");
	return nb_de_joueurs;
}


int* nbDeMouvement(int nb_de_joueurs){
    int i = 0;
    
	int* nb_mvt = malloc(sizeof(int) * nb_de_joueurs);
	if (nb_mvt == NULL){
	    printf("L'allocation de la mémoire pour le nombre de mouvement des joueurs a échouée.\n");
		exit(5);
	}

    while(i < (nb_de_joueurs)){

        // Ici, on n'utilise pas notre fonction "scanf_int" car on a besoin d'écrire le numéro du joueur à chaque demande
        int verif = 0;
        while (verif != 1 || nb_mvt[i] < 0){   
            printf("Le joueur %d donne le nombre de coups qu'il pense nécessaire pour atteindre la cible indiquée.\n", (i + 1));
            printf("Si vous pensez qu'elle est inatteignable, entrez 0.\n");
            verif = scanf("%d", &nb_mvt[i]);
            while(getchar() != '\n'){}
        }
        i++;
    }
    return nb_mvt;
}



// Cette fonction determine quel joueur joue
int joueurCommence(int nb_de_joueurs, int* nb_mvt){
    // On met le minimum très haut pour que les estimations des joueurs soient en dessous.
    // Il n'est pas initialisé à nb_mvt[0] car si le 1er joueur rentre zéro cela pose problème pour calculer le minimum hors 0
    int min = 0;
    int i_min = 0;

    for(int i = 0; i < nb_de_joueurs; i++){
	    // On a besoin de vérifier si tous les joueurs on rentrer 0 avant de trouver le minimum
		if(nb_mvt[i] > 0){
			min = nb_mvt[i];
            i_min = i;
		}
	}

    if (min == 0){ // Si tous les joueurs on rentrés 0
	    return -1;
	}

	for(int i = 0; i < nb_de_joueurs; i++){
	    // On prend le minimum au dessus de 0, le minimum restera 0 seulement si tous les joueurs rentre 0
		if((nb_mvt[i] < min) && (nb_mvt[i] > 0)){
			min = nb_mvt[i];
			i_min = i;
		}
	}
	
	return i_min;
}





void afficheLesChoix(int cibleChoisie, int robotChoisi){
    char couleurRobot[6];
    
    if(robotChoisi == 1){
        strcpy(couleurRobot,"Rouge");
    }
    else if(robotChoisi == 2){
        strcpy(couleurRobot,"Vert");
    }
    else if(robotChoisi == 3){
        strcpy(couleurRobot,"Bleu");
    }
    else{
        strcpy(couleurRobot,"Cyan");
    }
    couleur("47");
    couleur("30");
    printf("Vous devez vous rendre sur la cible %d en partant du robot %s.", cibleChoisie, couleurRobot);
    couleur("0");
    printf("\n");
}


// Cette fonction verifie si il y'a un mur et empêche le joueur d'avancer si tel est le cas
int mursRobot(Case** tab_jeu, int x, int y, int sens){

    /* On vérifie le bit placé à la position 0 pour gauche, 1 pour haut, 2 pour droite, et 3 pour bas
    afin savoir s'il y a des murs en fonction de la direction vers laquelle le robot se dirige */
    if(sens == HAUT){
        // Mur en haut ou en bas sur la case au dessus ou un autre robot
        if(((tab_jeu[y][x].murs & (1 << 1)) != 0) || ((tab_jeu[y - 1][x].murs & (1 << 3)) != 0) || (tab_jeu[y - 1][x].robot != 0)){
            return -1;
        }
    }
    else if(sens == BAS){
        // Mur en haut sur la case en dessous ou en bas ou un autre robot
        if(((tab_jeu[y + 1][x].murs & (1 << 1)) != 0) || ((tab_jeu[y][x].murs & (1 << 3)) != 0) || (tab_jeu[y + 1][x].robot != 0)){
            return -1;
        }
    }
    else if(sens == GAUCHE){
        // Mur à gauche ou mur à droite sur la case juste à gauche ou un autre robot
        if(((tab_jeu[y][x].murs & (1 << 0)) != 0) || ((tab_jeu[y][x - 1].murs & (1 << 2)) != 0) || (tab_jeu[y][x - 1].robot != 0)){
            return -1;
        }
    }
    else{
        // Mur à gauche ou mur à droite sur la case juste à gauche ou un autre robot
        if(((tab_jeu[y][x + 1].murs & (1 << 0)) != 0) || ((tab_jeu[y][x].murs & (1 << 2)) != 0) || (tab_jeu[y][x + 1].robot != 0)){
            return -1;
        }
    }

    return 1;
}




int deplacement(Case** tab_jeu, int* P_ligne, int* P_col, int* coordXRobot, int* coordYRobot, int robotChoisi){
    char char_saisi;

    char_saisi = scanf_char("Entrez les touches \"z\" \"q\" \"s\" ou \"d\" pour pour vous déplacer.\n");

    // On utilise le robot selectionné pour se déplacer
    tab_jeu[*coordYRobot][*coordXRobot].robot = 0;
    switch(char_saisi){
        case 'z' :
            for(int i = *coordYRobot; i > 0; i--){
                // On test si la direction est bloquée ou non
                if(mursRobot(tab_jeu, *coordXRobot, *coordYRobot, HAUT) != 1){
                    break;
                }
                *coordYRobot -= 1;
            }
            break;
        case 'q' :
            for(int i = *coordXRobot; i > 0; i--){
                if(mursRobot(tab_jeu, *coordXRobot, *coordYRobot, GAUCHE) != 1){
                    break;
                }
                *coordXRobot -= 1;
            }
            break;
        case 's' :
            for(int i = *coordYRobot; i < (*P_ligne - 1); i++){
                if(mursRobot(tab_jeu, *coordXRobot, *coordYRobot, BAS) != 1){
                    break;
                }
                *coordYRobot += 1;
            }
            break;
        case 'd' :
            for(int i = *coordXRobot; i < (*P_col - 1); i++){
                if(mursRobot(tab_jeu, *coordXRobot, *coordYRobot, DROITE) != 1){
                    break;
                }
                *coordXRobot += 1;
            }
            break;
        default :
        	tab_jeu[*coordYRobot][*coordXRobot].robot = robotChoisi;
            return 0;
    }

    // On redonne la valeur du robot à la case, qu'il se soit déplacer ou non
    tab_jeu[*coordYRobot][*coordXRobot].robot = robotChoisi;

    return 1;
}



int finDeManche(Case** tab_jeu, int coordXRobot, int coordYRobot, int cibleChoisie){
	if(tab_jeu[coordYRobot][coordXRobot].valeur == cibleChoisie){
	    printf("Le robot est sur la bonne cible\n");
		return 1;
	}
	return 0;
}


int* Attri_de_points(int nb_deplacement, int* nb_mvt, int* score, int joueur, int nb_de_joueurs){
    if(nb_deplacement > nb_mvt[joueur]){
        printf("Vous avez dépasser votre prédiction de coups pour atteindre la cible !\nVous avez perdu !\n");
        for(int i = 0; i < nb_de_joueurs; i++){
            if(i != joueur){
                score[i]++;
            }
        }
    }
    else if(nb_deplacement == nb_mvt[joueur]){
        printf("Bravo, vous avez atteint la cible !\n");
	    score[joueur] += 2;
    }
	else if(nb_deplacement < nb_mvt[joueur]){
	    printf("Dommage, vous avez atteint la cible trop vite !\n");
		score[joueur]--;
    }
    return score;
}



void afficheScore(int* score, int nb_de_joueurs){
    for(int i = 0; i < nb_de_joueurs; i++){
        printf("Le joueur %d possède : %d point(s).\n", i+1, score[i]);
    }
}




int manche(int* score, int nb_de_joueurs){
    int nb_deplacement = 0;
    int cibleChoisie = 0;
    int robotChoisi = 0;
    int coordXRobot = -1;
    int coordYRobot = -1;
    int resultat = 0;

    int* P_coordXRobot = &coordXRobot;
    int* P_coordYRobot = &coordYRobot;
    
    int ligne = 0;
    int col = 0;

    int* P_ligne = &ligne;
    int* P_col = &col;

    // Le tableau qui contiendra toutes les cases du jeu
    Case** tab_jeu = creerTabJeu(P_ligne, P_col);

    // Placement des murs tout autours du plateau
    mursBords(tab_jeu, P_ligne, P_col);
    mursParalleles(tab_jeu, P_ligne, P_col);

    creerCibles(tab_jeu, P_ligne, P_col); // Création des cibles
    creerRobots(tab_jeu, P_ligne, P_col); // Creation des robots

    // On choisi la cible et le robot qui vont être utilisés
    cibleChoisie = ChoixCible(tab_jeu, P_ligne, P_col);

    if (cibleChoisie <= 0){
        printf("La cible n'a pas pu être selectionnée\n");
        exit(1);
    }

    robotChoisi = ChoixRobot(tab_jeu, P_ligne, P_col, P_coordXRobot, P_coordYRobot);

    if (robotChoisi <= 0){
        printf("Le robot n'a pas pu être selectionné\n");
        exit(1);
    }

    afficheLesChoix(cibleChoisie, robotChoisi);
    
    afficheJeu(tab_jeu, P_ligne, P_col); // Affiche le plateau
    
    printf("Vous avez 30 secondes pour réfléchir\n");
    chronometre(30); // On lance le chronomètre

    // Demande aux joueurs de rentrer leurs nombres de mouvements
    int* nb_mvt = nbDeMouvement(nb_de_joueurs);
    
    // Le joueurs avec le plus petit nombre est celui qui joue
    int joueur = joueurCommence(nb_de_joueurs, nb_mvt);
    if (joueur == -1){
        printf("Aucun joueur ne joue, on recommence cette manche.\n");
        free(nb_mvt); // Libère la mémoire du tableau
        return -1;
    }
    
    couleur("47");
    couleur("30");
    printf("C'est le joueur %d qui va jouer cette manche.\n", joueur+1);
    couleur("0");
    
    
    // La boucle pour chaques tours de jeu
    for(int i = 0; i < nb_mvt[joueur] + 1; i++){
        afficheLesChoix(cibleChoisie, robotChoisi);
        afficheJeu(tab_jeu, P_ligne, P_col);
        resultat = deplacement(tab_jeu, P_ligne, P_col, P_coordXRobot, P_coordYRobot, robotChoisi);
        
        // Si le joueur ne s'est pas déplacé, le compteur n'augmente pas
        if (resultat == 1){
            nb_deplacement++;
        }
        else{
            i--;
        }
        printf("Le nombre de déplacements : %d\n", nb_deplacement);
        if(finDeManche(tab_jeu, coordXRobot, coordYRobot, cibleChoisie) == 1){
            break;
        }
        else if (nb_deplacement >= nb_mvt[joueur]){
            nb_deplacement++;
        	break;
        }
    }
    
    afficheJeu(tab_jeu, P_ligne, P_col);
    
    // Affiche le résultat et actualise les scores
    score = Attri_de_points(nb_deplacement, nb_mvt, score, joueur, nb_de_joueurs);
    
    // Affiche les nouveaux scores
    afficheScore(score, nb_de_joueurs);
    
    // On libère l'espace mémoire utilisé
    for(int i=0; i < (*P_ligne); i++){
        free(tab_jeu[i]);
    }
    free(tab_jeu);
    free(nb_mvt);
    
    return 1;
}

