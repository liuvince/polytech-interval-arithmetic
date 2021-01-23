#include <ieee754.h>
#include "conversion.h"
#include <stdio.h>
#include <math.h>
#include "struct.h"
#include "operation.h"
#include <fenv.h>

/*

// Fonction qui à partir d'un œFP_intervalle rend un centre et le rayon correspondant
double FPInterv2CenterRadius(FP_INTERV I,int *expR);

// Fonction qui à partir d'un centre et du rayon renvoie le FP_INTERV correspondant
FP_INTERV CenterRadius2FPInter(double c, int expR);

*/

// Function to perform sqrt function over FP-INTER format
FP_INTERV FpInterSqrt(FP_INTERV I)
{
	double centreSqrt,centreI;
	int exprSqrt,exprI;
	
	centreI = FPInterv2CenterRadius(I,&exprI);
	centreSqrt=sqrt(centreI);
	int e;
	frexp(centreI,&e);
	e--;
	fesetround(FE_UPWARD);
	double RadiusSqrt=fabs(centreI)-fabs(centreSqrt)-pow(2,exprI)+pow(2,-1074)+ pow(2,-53+e);
	fesetround(FE_DOWNWARD);	
	exprSqrt = (int) ceil(log(RadiusSqrt)/log(2));
	
	return CenterRadius2FPInter(centreSqrt, exprSqrt);

}

// Function to perform Exp function over FP-INTER format
FP_INTERV FpInterExp(FP_INTERV I)
{
	double centerExp;
	int exprExp;
	double RadiusExp;
	int expr;
	double center=FPInterv2CenterRadius(I,&expr);
	double a,b;
	fesetround(FE_DOWNWARD);
	a = center-pow(2,expr);
	fesetround(FE_UPWARD);
	b = center+pow(2,expr);
	fesetround(FE_TONEAREST);	
	centerExp = (exp(b)+exp(a))/2;
	fesetround(FE_UPWARD);
	int e;
	frexp(centerExp,&e);
	e--;
	RadiusExp = (exp(b)-exp(a))/2 + pow(2,-53+e) + pow(2,-1074);
	fesetround(FE_TONEAREST);
	
	exprExp = (int) ceil(log(RadiusExp)/log(2));


	return CenterRadius2FPInter(centerExp, exprExp);
}


// Function to perform Log function over FP-INTER format
FP_INTERV FpInterLog(FP_INTERV I)
{
	double center,centerLog;
	int expr,exprLog;
	double RadiusLog;

	// On recupere le rayon et le centre de 1 intervalle
	center = FPInterv2CenterRadius(I,&expr);

	double a,b;
	fesetround(FE_DOWNWARD);
	a = center-pow(2,expr);
	fesetround(FE_UPWARD);
	b = center+pow(2,expr);
	fesetround(FE_TONEAREST);
	centerLog = log(sqrt(a*b));
	fesetround(FE_UPWARD);
	int e;
	frexp(centerLog,&e);
	e--;
	RadiusLog = log(sqrt(b)/sqrt(a)) + pow(2,-53+e) + pow(2,-1074);
	fesetround(FE_TONEAREST);
	exprLog = (int) ceil(log(RadiusLog)/log(2));

	return CenterRadius2FPInter(centerLog, exprLog);
}
int in(double x,double a,double b)
{
	if (x >=a && x <= b)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Function to perform sinus function over FP-INTER format
FP_INTERV FpInterSin(FP_INTERV I)
{	
	double center,centerSin;
	int expr,exprSin;
	double RadiusSin;
	double rayon;

	// On recupere le rayon et le centre de 1 intervalle
	center = FPInterv2CenterRadius(I,&expr);
	rayon = pow(2,expr);
	double a,b;
	//center = modulo(center,(2*M_PI));
	//center = round(center) % round(2*M_PI);
	center = fmod(center,2*M_PI);
	//printf("center = %.52lf\n",center);
	double max,min;
	fesetround(FE_DOWNWARD);
	a = center-rayon;
	fesetround(FE_UPWARD);
	b = center+rayon;
	// CAS 1:
	// Cas 2
	fesetround(FE_TONEAREST);
	if (in(M_PI/2,a,b))
	{
		printf("Cas 1\n");
		// max = 1;
		min = fmin(sin(a),sin(b));
		if (in((3/2)*M_PI,a,b))
		{
				return CenterRadius2FPInter(0,0);
		}
		centerSin = (1 + min) /2;
		int e;
		frexp(centerSin,&e);
		e--;
		fesetround(FE_UPWARD);
		RadiusSin = fabs(1-min)/2+pow(2,-53+e);
		fesetround(FE_TONEAREST);
		exprSin = (int) ceil(log(RadiusSin)/log(2)) ;
		return CenterRadius2FPInter(centerSin, exprSin);
				
	}
	else
	{
		if (in((3/2)*M_PI,a,b))
		{		printf("Cas 2\n");
				max = fmax(sin(a),sin(b));
				min = -1;
				centerSin = (-1 + max) /2;
				int e;
				frexp(centerSin,&e);
				e--;
				fesetround(FE_UPWARD);
				RadiusSin = fabs(-1+max)/2+pow(2,-53+e);
				fesetround(FE_TONEAREST);
				exprSin = (int) ceil(log(RadiusSin)/log(2)) ;
				return CenterRadius2FPInter(centerSin, exprSin);			
		}
		else
		{
			printf("Cas 3\n");
			centerSin = (sin(a)+sin(b))/2;
			//printf("sin(a) = %.53lf sin(b) = %.53lf centersin = %.53lf \n\n",sin(a),sin(b),centerSin);
			int e;
			frexp(centerSin,&e);
			e--;
			fesetround(FE_UPWARD);
			RadiusSin = fabs(sin(b)-sin(a))/2+pow(2,-53+e);
			fesetround(FE_TONEAREST);
			exprSin = (int) ceil(log(RadiusSin)/log(2)) ;

			return CenterRadius2FPInter(centerSin, exprSin);
		}


	}
	
	
	/*
	if (2*(rayon) < M_PI / 2) // Si sin monotone sur I
	{
		centerSin = (sin(a)+sin(b))/2;
		int e;
		frexp(centerSin,&e);
		e--;
		RadiusSin = abs(sin(b)-sin(a))/2+pow(2,-53+e);
		exprSin = (int) ceil(log(RadiusSin)/log(2)) ;

		return CenterRadius2FPInter(centerSin, exprSin);
	}
	else
	{
		double min = fmin(sin(a),sin(b));
		double max = 1;
		
		
	}	*/



}

/* intel mkl: mathematical kernel library utiliser les blast pour faire du calcul matriciel par intervalle
// Function to perform cosinus function over FP-INTER format*/
FP_INTERV FpInterCos(FP_INTERV I)
{

	// On recupere le rayon et le centre de 1 intervalle
	int expr;
	double center = FPInterv2CenterRadius(I,&expr);
	center = center + M_PI/2;
	FP_INTERV newI = CenterRadius2FPInter(center,expr);
	FP_INTERV COS = FpInterSin(newI);
	return COS;
}

// Function to perform tan function over FP-INTER format
FP_INTERV FpInterTan(FP_INTERV I)
{
	return FpInterDivision(FpInterSin(I),FpInterCos(I));
}

