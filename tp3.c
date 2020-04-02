#include "tp3.h"
#include <stdio.h>

void remplirMat(matrice_creuse* m, int N, int M)
{
    int lignes = N;
    m->Nlignes = lignes;

    int colonnes = M;
    m->Ncolonnes = colonnes;

    printf("Entrez les valeurs de la matrice: \n");
    liste_ligne* currTableau = m->tableau;
    currTableau = (liste_ligne*)malloc(m->Nlignes * sizeof(liste_ligne*));

    for (int i = 0; i < lignes; i++) {
        liste_ligne currLigne;
        liste_ligne prev = NULL;
        for (int j = 0; j < colonnes; j++) {
            int valeur;
            scanf("%d", valeur);
            if (valeur != 0) {
                currLigne = (liste_ligne)malloc(sizeof(liste_ligne));
                currLigne->valeur = valeur;
                currLigne->indice = i;
                currLigne->next = NULL;
                if (prev != NULL) {
                    prev->next = currLigne;
                    prev = prev->next;
                } else { // Si valeur est la première qui vaut différente de 0, assigner prev et currTableau
                    currTableau[i] = prev = currLigne;
                }
            }
        }
    }
}