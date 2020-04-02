#ifndef TP3_H_INCLUDED

#define TP3_H_INCLUDED

// STRUCTURE ELEMENT
struct Element {
    int col;
    int val;
    struct Element* suivant;
};

typedef struct Element element;

// TYPE LISTE_LIGNE
typedef element* liste_ligne;

// STRUCTURE MATRICE CREUSE
struct MatriceCreuse {
    int Nlignes;
    int Ncolonnes;
    liste_ligne* tab_lignes;
};

typedef struct MatriceCreuse matrice_creuse;

void remplirMat(matrice_creuse* ma, int N, int M);

void afficherMat(matrice_creuse m);

int getValue(matrice_creuse m, int i, int j);

void putValue(matrice_creuse m, int i, int j, int val);

void addMat(matrice_creuse m1, matrice_creuse m2);

int nombreOctetsGagnes(matrice_creuse m1);

#endif // TP3_H_INCLUDED
