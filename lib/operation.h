#ifndef __ADDITION__H
#define __ADDITION__H

// Function to perform addition over FP-Intervalle format
FP_INTERV FpInterAdd(FP_INTERV A, FP_INTERV B);

// Function to perform substraction over FP-Intervalle format
FP_INTERV FpInterSub(FP_INTERV A, FP_INTERV B);

// Function to perform Multiplication over FP-INTTER format
FP_INTERV FpInterMult(FP_INTERV A, FP_INTERV B);

// Function to perform inversion over FP-INTER format
FP_INTERV FpInterInversion(FP_INTERV B);
FP_INTERV FpInterInversion2(FP_INTERV B);

// Function to perform division over FP-INTER format
FP_INTERV FpInterDivision(FP_INTERV A, FP_INTERV B);

// Function to perform intersection over FP-INTER format
FP_INTERV FpInterIntersection(FP_INTERV A, FP_INTERV B);


#endif
