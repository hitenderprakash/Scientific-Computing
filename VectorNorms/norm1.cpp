/* 
 * Hitender Prakash 
 * norm1.cpp - calculate l1 norm of a vector
 */
#include <iostream>
#include <cmath>
#include <vector>
// Function to calculate l1-norm of a vector
// norm1(int n, double *x) 
// input: n - size of vector, x - reference of vector
// output: (double) l1 norm
double norm1(int n, std::vector<double> &x){
	if(x.size()!=n){ return 0;}
	double norm_1=0.0;
	for(int i=0;i<n;i++){
		norm_1+=std::abs(x[i]);
	}
	return norm_1;
}
