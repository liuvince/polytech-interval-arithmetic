#include <ieee754.h>
#include "conversion.h"
#include <stdio.h>
#include <math.h>
#include "operation.h"
#include "struct.h"
#include "newton.h"
#include "function.h"
#include "matrice.h"

int main()
{
	
	
	// Parametre
	int exprA,exprB,exprC;
	double centreA,centreB,centreC;
	FP_INTERV A,B,C;
	
	int imax = 10;
	A = CenterRadius2FPInter(1.4, -5);

	B = newton( A,imax);
	//B = FpInterSin(A);

	FpInterBinaryPrint(B);
	//FpInterBinaryPrint(B);

	//doublePrint(sin(3.14));
	
	/*
	int i,j,row,col;
	FP_MATRIX * A,*B,*C;

	row = 2;
	col = 2;
	A = FpInterMatrixAlloc(row,col);
	B = FpInterMatrixAlloc(row,col);
	A->value[0][0] = CenterRadius2FPInter(2, -20);
	A->value[0][1] = CenterRadius2FPInter(1, -40);
	A->value[1][0] = CenterRadius2FPInter(3, -40);
	A->value[1][1] = CenterRadius2FPInter(1, -40);

	B->value[0][0] = CenterRadius2FPInter(1, -40);
	B->value[0][1] = CenterRadius2FPInter(4, -40);
	B->value[1][0] = CenterRadius2FPInter(1, -40);
	B->value[1][1] = CenterRadius2FPInter(5, -40);
	
	C = FpInterMatrixMult(A, B);
	FpInterMatrixPrint(C);
	FpInterMatrixFree(A);
	FpInterMatrixFree(B);
	FpInterMatrixFree(C);
	*/
	return 0;
		
	
}


