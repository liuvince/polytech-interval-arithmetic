#include "struct.h"

#ifndef __MATRICE__H
#define __MATRICE__H

typedef struct
{
	FP_INTERV ** value; // Valeur de la matrice
	int row; // Ligne
	int col; // Colonne
} FP_MATRIX;

// Allocation la mémoire
FP_MATRIX * FpInterMatrixAlloc(int row,int col);

// Produit matricielle
FP_MATRIX * FpInterMatrixMult(FP_MATRIX * A, FP_MATRIX * B);

// Liberation de la mémoire
void FpInterMatrixFree(FP_MATRIX * A);

// Affichage
void FpInterMatrixPrint(FP_MATRIX *A);


#endif
