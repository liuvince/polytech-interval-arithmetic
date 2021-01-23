#include <ieee754.h>
#include "conversion.h"
#include <stdio.h>
#include <math.h>
#include "struct.h"
#include "operation.h"
#include "matrice.h"
#include <stdlib.h>

// Allocation la mémoire
FP_MATRIX * FpInterMatrixAlloc(int row,int col)
{	
	// Alouer la zone mémoire de la structure
	FP_MATRIX * elem = (FP_MATRIX *) malloc(sizeof(FP_MATRIX));
	// Alouer la zone mémoire pour les valeurs
	elem->value = (FP_INTERV **) malloc(row*sizeof(FP_INTERV *));
	int i,j;
	for(i=0;i<row;i++)
	{
		elem->value[i] = (FP_INTERV *) malloc(col*sizeof(FP_INTERV));
	}
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			elem->value[i][j] = 0;
		}
	}
	elem->row = row;
	elem->col = col;
	return elem;
}

// Produit matricielle
FP_MATRIX * FpInterMatrixMult(FP_MATRIX * A, FP_MATRIX * B)
{
	if (A->col != B->row)
	{
		fprintf(stderr,"Problème de dimension ! \n");
		exit(EXIT_FAILURE);
	}
	// C = A * B
	FP_MATRIX * C = FpInterMatrixAlloc(A->row,B->col);
	int i,j,k;
	for(i=0;i<A->row;i++)
	{
		for(j=0;j<B->col;j++)
		{
			for(k=0;k<A->col;k++)
			{
				C->value[i][j] = FpInterAdd(C->value[i][j], FpInterMult(A->value[i][k],B->value[k][j]));
				// normalement: C[i][j] += a[i][k] * b[k][j]
			}
		}
	}
	return C;
}

// Liberation de la mémoire
void FpInterMatrixFree(FP_MATRIX * A)
{
	int i;
	if (A)
	{
		for(i=0;i<A->row;i++)
		{
			free(A->value[i]);
		}
		free(A->value);
		free(A);
	}
}

// Affichage
void FpInterMatrixPrint(FP_MATRIX *A)
{ 	
	int i,j;

	for(i=0;i<A->row;i++)
	{
		for(j=0;j<A->col;j++)
		{
			printf("[%d,%d]\n",i+1,j+1);
			FpInterBinaryPrint(A->value[i][j]);
		}	

	}

}




