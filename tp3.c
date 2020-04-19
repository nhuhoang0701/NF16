#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

/***********************Fonctions Supplementaires***************************/

void push(liste_ligne* head_ref, int val, int j)
{
    liste_ligne new_node = (liste_ligne)malloc(sizeof(element));

    new_node->val = val;
    new_node->col = j;
    new_node->suivant = (*head_ref);
    (*head_ref) = new_node;
}

void insertAfter(liste_ligne prev, int val, int col)
{
    liste_ligne new_node = (liste_ligne)malloc(sizeof(element));
    new_node->val = val;
    new_node->col = col;
    new_node->suivant = prev->suivant;
    prev->suivant = new_node;
}

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
        printf("Il est impossble de trouver cette cellule\n");
        return EXIT_FAILURE;
    }
    liste_ligne ithLigne = m.tab_lignes[i];
    while (ithLigne != NULL && ithLigne->col < j) {
        ithLigne = ithLigne->suivant;
    }

    if (ithLigne == NULL) {
        return 0;
    }
    // ithLigne pas NULL
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
        printf("Il est impossble de trouver cette cellule\n");
        return;
    }

    liste_ligne ithLigne = m.tab_lignes[i];
    liste_ligne prev = NULL;

    while (ithLigne != NULL && ithLigne->col < j) {

        prev = ithLigne;
        ithLigne = ithLigne->suivant;
    }
    if (prev == NULL) {

        liste_ligne* temp = &ithLigne;
        push(temp, val, j);
        m.tab_lignes[i] = *temp;

    } else if (ithLigne == NULL || ithLigne->col > j) {

        insertAfter(prev, val, j);

    } else if (j == ithLigne->col) {

        ithLigne->val = val;
    }
    printf("La matrice est mis a jour\n");
    return;
}

/*********************************-5-***************************************/
void addMat(matrice_creuse m1, matrice_creuse m2)
{
    if (m1.Ncolonnes != m2.Ncolonnes || m1.Nlignes != m2.Nlignes) {
        printf("2 matrices ont les dimensions differentes\n");
        return;
    }
    int lignes = m1.Nlignes;

    for (int i = 0; i < lignes; i++) {

        liste_ligne m1_ithLigne = m1.tab_lignes[i];
        liste_ligne m2_ithLigne = m2.tab_lignes[i];
        liste_ligne premier = NULL;

        while (m1_ithLigne != NULL && m2_ithLigne != NULL) {

            int m1_col = m1_ithLigne->col;
            int m2_col = m2_ithLigne->col;

            if (m1_col == m2_col) {
                premier = m1_ithLigne;
                m1_ithLigne->val += m2_ithLigne->val;
                m1_ithLigne = m1_ithLigne->suivant;
            } else if (m1_col > m2_col) {
                if (premier == NULL) {
                    premier = (liste_ligne)malloc(sizeof(element));
                    premier->val = m2_ithLigne->val;
                    premier->col = m2_col;
                    premier->suivant = m1_ithLigne;
                    m1.tab_lignes[i] = premier;
                } else {
                    insertAfter(premier, m2_ithLigne->val, m2_col);
                    premier = premier->suivant;
                }
            } else if (m1_col < m2_col) {
                if (premier != NULL) {
                    premier->suivant = m1_ithLigne;
                }

                while (m1_ithLigne != NULL && m1_ithLigne->col < m2_col) {
                    premier = m1_ithLigne;
                    m1_ithLigne = m1_ithLigne->suivant;
                }

                if (m1_ithLigne == NULL) {
                    break;
                }

                if (m1_ithLigne->col == m2_col) {
                    premier = m1_ithLigne;
                    m1_ithLigne->val += m2_ithLigne->val;
                    m1_ithLigne = m1_ithLigne->suivant;
                } else {
                    insertAfter(premier, m2_ithLigne->val, m2_col);
                    premier = premier->suivant;
                }
            }
            m2_ithLigne = m2_ithLigne->suivant;
        }

        if (m1_ithLigne == NULL && m2_ithLigne != NULL) {
            if (premier == NULL) {
                premier = (liste_ligne)malloc(sizeof(element));
                premier->val = m2_ithLigne->val;
                premier->col = m2_ithLigne->col;
                premier->suivant = NULL;
                m1.tab_lignes[i] = premier;
                m2_ithLigne = m2_ithLigne->suivant;
            }
            while (m2_ithLigne != NULL) {
                insertAfter(premier, m2_ithLigne->val, m2_ithLigne->col);
                premier = premier->suivant;
                m2_ithLigne = m2_ithLigne->suivant;
            }
        }
    }
    printf("Les 2 matrices sont ete ajoutes\n");
    return;
}

/*********************************-6-***************************************/

int nombreOctetsGagnes(matrice_creuse m)
{
    int taille_classique = (int)((m.Ncolonnes * m.Nlignes) * (sizeof(int)));
    int taille_economise = (int)(sizeof(liste_ligne*) + 2 * sizeof(int));

    for (int i = 0; i < m.Nlignes; i++) {
        liste_ligne currLigne = m.tab_lignes[i];
        taille_economise += (int)(sizeof(liste_ligne));
        while (currLigne != NULL) {
            taille_economise += (int)((sizeof(liste_ligne) + 2 * sizeof(int)));
            currLigne = currLigne->suivant;
        }
    }
    return taille_classique - taille_economise;
}
