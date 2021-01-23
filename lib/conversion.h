#include "struct.h"

#ifndef __CONVERSION__H
#define __CONVERSION__H

// Fonction qui à partir d'un œFP_intervalle rend un centre et le rayon correspondant
double FPInterv2CenterRadius(FP_INTERV I,int *expR);

// Fonction qui à partir d'un centre et du rayon renvoie le FP_INTERV correspondant
FP_INTERV CenterRadius2FPInter(double c, int expR);

// Fonction qui à partir d'un flottant en double précision renvoie le FP_INTERV correspondant
FP_INTERV double2FpInter(double c);


// Affiche l'intervalle
int FpInterBinaryPrint(FP_INTERV I);

int doublePrint(FP_INTERV I);

#endif
