/* 
 * Hitender Prakash 
 * norm2.c - calculate l2 norm of a vector
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to calculate l2-norm of a vector
// norm2(int n, double *x) 
// input: n - size of vector, x - reference of vector
// output: (double) l2 norm
double norm2(int n, double *x){
	if(!x){ return 0;}
	int i=0;
	double sqSum=0.0;
	double norm_2=0.0;
	for(i=0;i<n;i++){
		sqSum+=(x[i])*(x[i]);
	}
	norm_2=sqrt(sqSum);
	return norm_2;
}
