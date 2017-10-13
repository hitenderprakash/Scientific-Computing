/* 
 * Hitender Prakash 
 * norminf.c - calculate infinity norm of a vector
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to calculate infinity-norm of a vector
// norminf(int n, double *x) 
// input: n - size of vector, x - reference of vector
// output: (double) infinity norm

double norminf(int n, double *x){
	if(!x){ return 0;}
	int i=0;
	double norm_inf=abs(x[0]);
	for(i=1;i<n;i++){
		norm_inf=(norm_inf > abs(x[i]))? norm_inf : abs(x[i]);
	}
	return norm_inf;
}
