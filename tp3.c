#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

/*********************************-1-***************************************/

void remplirMat(matrice_creuse* m, int N, int M)
{
    int lignes = N;
    m->Nlignes = lignes;

    int colonnes = M;
    m->Ncolonnes = colonnes;

    printf("Entrez les valeurs de la matrice: \n");
    m->tab_lignes = (liste_ligne*)malloc(m->Nlignes * sizeof(liste_ligne));

    // Mettre à jour la matrice
    for (int i = 0; i < lignes; i++) {

        liste_ligne currLigne;
        liste_ligne prev = NULL;

        // Mettre à jour la ligne
        for (int j = 0; j < colonnes; j++) {

            // lire la valeur
            int valeur;
            scanf("%d", &valeur);

            if (valeur != 0) {
                currLigne = (liste_ligne)malloc(sizeof(element));
                currLigne->val = valeur;
                currLigne->col = j;
                currLigne->suivant = NULL;

                if (prev != NULL) {
                    prev->suivant = currLigne;
                    prev = prev->suivant;
                }
                // Si valeur est la première qui vaut différente de 0, assigner prev et currTableau
                else {
                    m->tab_lignes[i] = prev = currLigne;
                }
            }
        }
    }
}

/*********************************-2-***************************************/

void afficherMat(matrice_creuse m)
{

    int lignes = m.Nlignes;
    int colonnes = m.Ncolonnes;

    // Imprimer la tableau
    for (int i = 0; i < lignes; i++) {
        liste_ligne currLigne = m.tab_lignes[i];

        // se sert à imprimer la valeur 0
        int premier = -1, dernier = colonnes - 1;

        // Si la ligne est toute 0, les imprimer
        if (currLigne == NULL) {
            for (int i = 0; i < colonnes; i++) {
                printf("0 ");
            }
        }
        // Sinon ...
        else {
            // Imprimer chaque ligne
            while (currLigne != NULL) {

                // Imprimer les valeur 0
                for (int j = 0; j < currLigne->col - premier - 1; j++) {
                    printf("0 ");
                }

                printf("%d ", currLigne->val);
                premier = currLigne->col;
                currLigne = currLigne->suivant;
            }

            // Imprimer les valeur 0 à la fin de la ligne
            for (int i = 0; i < dernier - premier; i++) {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

/*********************************-3-***************************************/

int getValue(matrice_creuse m, int i, int j)
{
    if ((i < 0 || i > m.Nlignes) || (j < 0 || j > m.Ncolonnes)) {
        return EXIT_FAILURE;
    }
    liste_ligne ithLigne = m.tab_lignes[i];
    while (ithLigne != NULL && ithLigne->col < j) {
        ithLigne = ithLigne->suivant;
    }
    if (j == ithLigne->col) {
        return ithLigne->val;
    } else {
        return 0;
    }
}

/*********************************-4-***************************************/

void putValue(matrice_creuse m, int i, int j, int val)
{
    if ((i < 0 || i > m.Nlignes) || (j < 0 || j > m.Ncolonnes)) {
        return EXIT_FAILURE;
    }
    liste_ligne ithLigne = m.tab_lignes[i];
    while (ithLigne != NULL && ithLigne->col < j) {
        ithLigne = ithLigne->suivant;
    }
    if (j == ithLigne->col) {
        ithLigne->val = val;
        return;
    }
}

/*********************************-5-***************************************/
void addMat(matrice_creuse m1, matrice_creuse m2)
{
    if (m1.Ncolonnes != m2.Ncolonnes || m1.Nlignes != m2.Nlignes) {
        return;
    }
    int lignes = m1.Nlignes;

    for (int i = 0; i < lignes; i++) {
        liste_ligne m1_ithLigne = m1.tab_lignes[i];
        liste_ligne m2_ithLigne = m2.tab_lignes[i];

        while (m1_ithLigne != NULL && m2_ithLigne != NULL) {
            int m1_col = m1_ithLigne->col;
            int m2_col = m2_ithLigne->col;
            if (m1_col == m2_col) {
                m1_ithLigne->val += m2_ithLigne->val;
            } else if (m1_col < m2_col) {

                while (m1_ithLigne->col < m2_ithLigne->col) {
                    m1_ithLigne = m1_ithLigne->suivant;
                }
            } else {
            }
        }
    }
}
