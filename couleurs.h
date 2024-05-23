#ifndef COULEURS
#define COULEURS

#include <stdio.h>


#define suppr_ecran() printf("\033[H\033[2J")

#define couleur(param) printf("\033[%sm",param)

#endif