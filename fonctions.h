#ifndef FONCTIONS_H
#define FONCTIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define suppr_ecran() printf("\033[H\033[2J")

#define couleur(param) printf("\033[%sm",param)


#define GAUCHE 1
#define HAUT 2
#define DROITE 4
#define BAS 8

typedef struct{
    int valeur;
    int murs;
    int robot;
} Case;


int scanf_int(char* message);

char scanf_char(char* message);

void afficheJeu(Case** tab_jeu, int* P_ligne, int* P_col);

int mursAutorise(Case** tab_jeu, int* P_ligne, int* P_col, int mur_haut, int mur_bas, int mur_gauche, int mur_droite);

void mursParalleles(Case** tab_jeu, int* P_ligne, int* P_col);

void mursBords(Case** tab_jeu, int* P_ligne, int* P_col);

void mursCibles(Case** tab_jeu, int i, int j);

int cibleAutorise(Case** tab_jeu, int i, int j);

void creerCibles(Case** tab_jeu, int* P_ligne, int* P_col);

void creerRobots(Case** tab_jeu, int* P_ligne, int* P_col);

void initCasesJeu(Case** tab_jeu, int* P_ligne, int* P_col);

Case** creerTabJeu(int* P_ligne, int* P_col);

int ChoixCible(Case** tab_jeu, int* P_row, int* P_col);

int ChoixRobot(Case** tab_jeu, int* P_row, int* P_col, int* coordXRobot, int* coordYRobot);

void chronometre(int s);

int nbDeJoueurs(void);

int* nbDeMouvement(int nb_de_joueurs);

int joueurCommence(int nb_de_joueurs, int* nb_mvt);

void afficheLesChoix(int cibleChoisie, int robotChoisi);

int mursRobot(Case** tab_jeu, int x, int y, int sens);

int mursRobot(Case** tab_jeu, int x, int y, int sens);

int deplacement(Case** tab_jeu, int* P_ligne, int* P_col, int* coordXRobot, int* coordYRobot, int robotChoisi);

int finDeManche(Case** tab_jeu, int coordXRobot, int coordYRobot, int cibleChoisie);

int* Attri_de_points(int nb_deplacement, int* nb_mvt, int* score, int joueur, int nb_de_joueurs);

void afficheScore(int* score, int nb_de_joueurs);

int manche(int* score, int nb_de_joueurs);

int main(void);

#endif
