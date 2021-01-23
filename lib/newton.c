#include <ieee754.h>
#include "conversion.h"
#include <stdio.h>
#include <math.h>
#include "operation.h"
#include "struct.h"
#include <fenv.h>

// Newton method to obtain Sqrt(2)
FP_INTERV newton(FP_INTERV A, int imax)
{
	
	FP_INTERV I = A;
	FP_INTERV res;
	FP_INTERV Inv = 0;
	int exprI,exprInv,exprX;
	double xs;
	double x;
	double centreInv,centrexInv,rayonxInv;
	int i;
	FP_INTERV X;
	double centre;
	int e;
	double test1;
	int test2;

	for (i = 0;i<imax;i++)
	{
		xs = FPInterv2CenterRadius(I,&exprI);
		X = I;
		I = CenterRadius2FPInter(2*xs,exprI+1);

		Inv = FpInterInversion2(I);
		centreInv = FPInterv2CenterRadius(Inv,&exprInv);
		x = xs*xs-2;
		centrexInv = -centreInv * x;
		frexp(centrexInv,&e);
		e--;
	//fesetround(FE_UPWARD);
		rayonxInv = pow(2,exprInv)*x + pow(2,53-e);


		centre = centrexInv + xs;
	//fesetround(FE_TONEAREST);
		exprX= (int) ceil(log(fabs(rayonxInv))/log(2));

		I = CenterRadius2FPInter(centre,exprX);
		res = X;

		if (FpInterIntersection(I,X) == I)
		{
			res = X;
		}
		FpInterBinaryPrint(X);
test1 = FPInterv2CenterRadius(X,&test2);
	//test2--;
		printf("centre = %.16lf Rayon = %d \n",test1,test2);	
	

	}

	return res;

}



