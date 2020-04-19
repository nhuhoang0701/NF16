#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main()
{
    int choix;
    matrice_creuse* arrMatrices[MAX];
    for (int i = 0; i < MAX; i++) {
        arrMatrices[i] = NULL;
    }
    // Implémentation
    do {

        int nombre;
        int indice, ligne, colonne, val;
        int indice_1, indice_2;
        printf("Quel est votre choix?\n");
        printf("1 : Remplir des matrices\n"
               "2 : Afficher des matrices\n"
               "3 : Obtenir de value d'une matrice\n"
               "4 : Mettre une nouvelle value pour une matrice\n"
               "5 : Ajouter 2 matrices\n"
               "6 : Voir le gain en espace d'une matrice\n"
               "7 : Quitter le programme\n");

        printf("> ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            // Choix de nombre de matrice
            printf("Combien matrices voulez-vous?\n"
                   "> ");
            scanf("%d", &nombre);

            for (int i = 0; i < nombre; i++) {
                arrMatrices[i] = (matrice_creuse*)malloc(sizeof(matrice_creuse));
                printf("Matrice %d:\n", i);
                printf("Entrez le nombre de ligne et colonne:\n"
                       "> ");
                int n, m;
                scanf("%d%d", &n, &m);
                remplirMat(arrMatrices[i], n, m);
                // afficherMat(*arrMatrices[i]);
            }
            break;
        case 2:
            printf("Quelle matrice voulez-vous afficher?\n"
                   "> ");
            scanf("%d", &indice);
            if (arrMatrices[indice] == NULL) {
                printf("Vous n'avez pas encore la remplir! Veuillez essayer à nouveau ...\n");
            } else {
                afficherMat(*arrMatrices[indice]);
            }
            break;
        case 3:
            printf("Veuillez entrer l'indice de la matrice, la ligne et la colonne: \n"
                   "> ");
            scanf("%d%d%d", &indice, &ligne, &colonne);
            if (arrMatrices[indice] == NULL) {
                printf("Vous n'avez pas encore la remplir! Veuillez essayer à nouveau ...\n");
            } else {
                printf("la value de la cellule aux ligne %d et colonne %d de la matrice %d est: ", ligne, colonne, indice);
                printf("%d", getValue(*arrMatrices[indice], ligne, colonne));
            }
            break;
        case 4:
            printf("Veuillez entrer l'indice de la matrice, la ligne, la colonne et la nouvelle value:\n"
                   "> ");
            scanf("%d%d%d%d", &indice, &ligne, &colonne, &val);
            if (arrMatrices[indice] == NULL) {
                printf("Vous n'avez pas encore la remplir! Veuillez essayer à nouveau ...\n");
            } else {
                putValue(*arrMatrices[indice], ligne, colonne, val);
            }
            break;
        case 5:
            printf("Veuillez entrer 2 matrices que vous voulez ajouter: \n"
                   ">");
            scanf("%d%d", &indice_1, &indice_2);
            if (arrMatrices[indice_1] == NULL) {
                printf("Vous n'avez pas encore remplir la matrice %i! Veuillez essayer à nouveau ...\n", indice_1);
            } else if (arrMatrices[indice_2] == NULL) {
                printf("Vous n'avez pas encore remplir la matrice %i! Veuillez essayer à nouveau ...\n", indice_2);
            } else {
                printf("Affichage de la matrice %d:\n", indice_1);
                afficherMat(*arrMatrices[indice_1]);
                printf("Affichage de la matrice %d:\n", indice_2);
                afficherMat(*arrMatrices[indice_2]);
                addMat(*arrMatrices[indice_1], *arrMatrices[indice_2]);
                printf("Affichage de la nouvelle matrice %d:\n", indice_1);
                afficherMat(*arrMatrices[indice_1]);
            }
            break;
        case 6:
            printf("Quelle matrice voulez-vous afficher le gain en espace?\n"
                   "> ");
            scanf("%d", &indice);
            if (arrMatrices[indice] == NULL) {
                printf("Vous n'avez pas encore la remplir! Veuillez essayer à nouveau ...\n");
            } else {
                printf("Economiser %d octets\n", nombreOctetsGagnes(*arrMatrices[indice]));
            }
            break;
        case 7:
            printf("Au revoir!\n");
            break;
        default:
            printf("Choisir a nouveau !\n");
            break;
        }
        if (choix != 7) {
            printf("\nAppuyer sur nimporte quelle touche pour continuer...");
            getchar();
            getchar();
            printf("\n==============================================================\n\n");
        }
    } while (choix != 7);

    // Free toutes les resources
    for (int i = 0; i < MAX; i++) {
        if (arrMatrices[i] != NULL) {
            int lignes = arrMatrices[i]->Nlignes;
            for (int j = 0; j < lignes; j++) {

                // free pointeur type de element*
                free((arrMatrices[i]->tab_lignes)[j]);
            }
            // free pointeur type de liste_ligne*
            free(arrMatrices[i]->tab_lignes);

            // free pointeur type de matrice_creuse*
            free(arrMatrices[i]);
        }
    }
    return 0;
}
