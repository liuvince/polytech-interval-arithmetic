#include <ieee754.h>
#include "conversion.h"
#include <stdio.h>
#include <math.h>
#include "struct.h"
#include <fenv.h>

// Functions to perform addition over FP-INTER format
FP_INTERV FpInterAdd(FP_INTERV A, FP_INTERV B)
	{

	int exprA, exprB, exprC;
	double rayonC, centreA, centreB, centreC;

	if (A == 0)
	{
		return B;
	}
	if (B ==0)
	{
		return A;
	}
	
	// On recupere le rayon et le centre des 2 intervalles
	centreA = FPInterv2CenterRadius(A,&exprA);
	centreB = FPInterv2CenterRadius(B,&exprB);

	// nouveau centre: Arrondi de C1 + C2
	centreC = centreA + centreB;
	
	int e;
	// On recupere la puissance de 2 du centre
	frexp(centreC,&e);
	e = e - 1;
	// On calcule le nouveau rayon
	fesetround(FE_UPWARD);
	rayonC = pow(2,exprA) + pow(2,exprB) + pow(2,-53+e);
	fesetround(FE_TONEAREST);
	//frexp(rayonC,&e);
	// On calcule la puissance de 2 du rayon
	exprC = (int) ceil(log(rayonC)/log(2)) ;

	return CenterRadius2FPInter(centreC,exprC);

	}

// Functions to perform sub over FP-INTER format
FP_INTERV FpInterSub(FP_INTERV A, FP_INTERV B)
	{

	int exprA,exprB,exprC;
	double centreA,centreB,centreC;

	double rayonC;

	centreA = FPInterv2CenterRadius(A,&exprA);
	centreB = FPInterv2CenterRadius(B,&exprB);

	if (A == 0){
		return CenterRadius2FPInter(-centreB,exprA);
	}
	if (B == 0){
		return A;
	}
	// nouveau centre: Arrondi de C1 - C2
	centreC = centreA - centreB;

	int e;
	// On recupere la puissance de 2 du centre
	frexp(centreC,&e);
	e = e -1;

	// On calcule le nouveau rayon
	fesetround(FE_UPWARD);
	rayonC = pow(2,exprA) + pow(2,exprB) + pow(2,-53+e);
	fesetround(FE_TONEAREST);
	// On calcule la puissance de 2 du rayon
	exprC = (int) ceil(log(rayonC)/log(2));

	return CenterRadius2FPInter(centreC,exprC);

	}

// Function to perform Multiplication over FP-INTTER format
FP_INTERV FpInterMult(FP_INTERV A, FP_INTERV B)
	{
	int exprA,exprB,exprC;
	double centreA,centreB,centreC;

	double RadiusC;

	// On recupere le centre et le rayon des 2 intervalles
	centreA = FPInterv2CenterRadius(A,&exprA);
	centreB = FPInterv2CenterRadius(B,&exprB);
	// nouveau centre: Arrondi de C1 * C2
	centreC = centreA * centreB;
	int e;
	frexp(centreC,&e);
	e = e -1;

	// On calcule le nouveau rayon
	fesetround(FE_UPWARD);
	RadiusC = pow(2,-1074)+ pow(2,-53+e)+(fabs(centreA)+pow(2,exprA))*pow(2,exprB)+pow(2,exprA)*fabs(centreB);
	fesetround(FE_TONEAREST);
	// On calcule la puissance de 2 du rayon
	exprC = (int) ceil(log(RadiusC)/log(2));

	return CenterRadius2FPInter(centreC,exprC);
	}

// Function to perform inversion over FP-INTER format
FP_INTERV FpInterInversion(FP_INTERV B)
	{
		int exprB,exprInvB;
		int sign;
		double centreB,centreInvB,rayonInvB;
		double C1,C2;
		// On recupere le centre et le rayon de l'intervalle
		centreB = FPInterv2CenterRadius(B,&exprB);

		if(centreB >0){sign = 1;}
		else {sign = -1;}
		// Bornes de l'intervalle inverse en infimum-supremum
		C1 = -1/(-fabs(centreB)-pow(2,exprB));
		int e1;
		frexp(C1,&e1);
		e1--;

	
		C2 = -1/(-fabs(centreB)+pow(2,exprB));
		int e2;
		frexp(C2,&e2);
		e2--;

		//Centre de l'intervalle
		centreInvB = C1 - 0.5*(C2-C1);


		int e;
		frexp(centreInvB,&e);
		e--;
		
		// Rayon de l'intervalle
		rayonInvB = fabs(centreInvB - C1) + pow(2,e-52);
		
		exprInvB = (int)ceil(log(rayonInvB)/log(2));
		centreInvB = sign*centreInvB;


		return CenterRadius2FPInter(centreInvB,exprInvB);
	}

// Function to perform division over FP-INTER format
FP_INTERV FpInterDivision(FP_INTERV A, FP_INTERV B)
	{
		FP_INTERV InvB = FpInterInversion(B);
		return FpInterMult(A,InvB);
	}


FP_INTERV FpInterIntersection(FP_INTERV A, FP_INTERV B)
{

	int exprA, exprB;
	double centreA, centreB;

	centreA = FPInterv2CenterRadius(A,&exprA);
	centreB = FPInterv2CenterRadius(B,&exprB);

	int expr1, expr2;
	double c1,c2;
	

	// Cas 1 : les deux centres sont égaux
	if (centreA == centreB)
	{
		return CenterRadius2FPInter(centreA,fmin(exprA,exprB));

	}
	// Cas 2 : les deux centres ne sont pas égaux
	// On définit c1 comme le plus petit centre, et c2 comme le plus grand centre 
	if (centreA > centreB)
	{
		c2 = centreA;
		expr2 = exprA;
		c1 = centreB;
		expr1 = exprB;
	}
	else
	{
		c1 = centreA;
		expr1 = exprA;
		c2 = centreB;
		expr2 = exprB;
	}

	
	double dist = fabs(c2-c1);

	// Cas 2a: Les deux ensembles sont disjoints
	if ( (pow(2,expr1) + pow(2,expr2) ) < dist) 
	{ 
		return 0; 
	}
	// Cas 2b: <c1,r1> est inclus <c2,r2>
	if ( (dist + pow(2,expr1) ) < pow(2,expr2) )
	{
		return CenterRadius2FPInter(c1,expr1);
	}
	
	// Cas 2c: <c2,r2> est inclus dans <c1,r1>
	if ( dist + pow(2,expr2) < pow(2,expr1) )
	{
		return CenterRadius2FPInter(c2,expr2);
	}


	double c3;
	int expr3;
	double r3;
	int e;

	// Cas 3: on doit faire le calcul de l'intersection
	
	// Calcul du nouveau centre
	c3 = 0.5*(c1+ pow(2,expr1) - pow(2,expr2) + c2);

	// On recupere la puissance de 2 de c3
	frexp(c3,&e);
	e = e -1;

	// On calcul le nouveau rayon
	fesetround(FE_UPWARD);
	r3 = 0.5*(c1-c2+pow(2,expr1) + pow(2,expr2) )+ pow(2,-53+e);
	fesetround(FE_TONEAREST);
	// On recupere la puissance de 2 du nouveau rayon
	expr3 = (int) ceil(log(r3)/log(2)) ;
	

	return CenterRadius2FPInter(c3,expr3);
	

}



FP_INTERV FpInterInversion2(FP_INTERV B)
{


	int  exprB, exprInvB;
	double rayonB, rayonInvB;
	double centreB,centreInvB;

	if (B == 0)
	{
		return B;
	}
	
	// On recupere le rayon et le centre des 2 intervalles
	centreB = FPInterv2CenterRadius(B,&exprB);
	fesetround(FE_UPWARD);
	double D = centreB *centreB - pow(2,exprB)*pow(2,exprB);
	fesetround(FE_TONEAREST);
	centreInvB = centreB / D;

	
	int e;
	// On recupere la puissance de 2 du centre
	frexp(centreInvB,&e);
	e = e - 1;
	// On calcule le nouveau rayon
	fesetround(FE_UPWARD);
	rayonInvB =  pow(2,-1074)+ pow(2,-53+e)+pow(2,exprB)/D;
	fesetround(FE_TONEAREST);

	exprInvB = (int) ceil(log(rayonInvB)/log(2)) ;

	return CenterRadius2FPInter(centreInvB,exprInvB);

}





