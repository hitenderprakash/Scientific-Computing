/* 
 * Hitender Prakash 
 * norm1.c - calculate l1 norm of a vector
 */
#include <stdio.h>
#include <stdlib.h>

// Function to calculate l1-norm of a vector
// norm1(int n, double *x) 
// input: n - size of vector, x - reference of vector
// output: (double) l1 norm
double norm1(int n, double *x){
	if(!x){ return 0;}
	int i=0;
	double norm_1=0.0;
	for(i=0;i<n;i++){
		norm_1+=abs(x[i]);
	}
	return norm_1;
}
