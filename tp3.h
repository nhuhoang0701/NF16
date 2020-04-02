#ifndef TP3_H
#define TP3_H

#include <stdlib.h>

/*******************************************************
                        TYPES
 *******************************************************/

// Définir la type << element >>
typedef struct element {
    int indice;
    int valeur;
    struct element* next;
} element;

// << liste_ligne >> remplace pour << struct Element* >>
typedef element* liste_ligne;

// Définir la type << matrice_creuse >>
typedef struct
{
    int Nlignes, Ncolonnes;
    liste_ligne* tableau;
} matrice_creuse;


/*******************************************************
                        FONCTIONS
 *******************************************************/

void remplirMat(matrice_creuse* m, int N, int M);

void afficherMat(matrice_creuse m);

int getValue(matrice_creuse m, int i, int j);

void putValue(matrice_creuse m, int i, int j, int val);

void addMat(matrice_creuse m1, matrice_creuse m2);

int nombreOctetsGagnes(matrice_creuse m1);

#endif // !TP3_H
