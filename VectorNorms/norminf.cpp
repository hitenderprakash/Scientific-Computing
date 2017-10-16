/* 
 * Hitender Prakash 
 * norminf.cpp - calculate infinity norm of a vector
 */
#include <iostream>
#include <cmath>
// Function to calculate infinity-norm of a vector
// norminf(int n, double *x) 
// input: n - size of vector, x - reference of vector
// output: (double) infinity norm
using namespace std;
double norminf(int n, double *x){
	if(!x){ return 0;}
	double norm_inf=std::fabs(x[0]);
	for(int i=1;i<n;i++){
		double temp=std::fabs(x[i]);
		norm_inf=max(norm_inf,temp);
		//norm_inf=(norm_inf > temp)?norm_inf : temp;
	}
	return norm_inf;
}
