/* 
 * Hitender Prakash 
 * norminf.cpp - calculate infinity norm of a vector
 */
#include <iostream>
#include <cmath>
#include <vector>
// Function to calculate infinity-norm of a vector
// norminf(int n, double *x) 
// input: n - size of vector, x - reference of vector
// output: (double) infinity norm
using namespace std;
double norminf(int n, std::vector<double> &x){
	if(x.size()!=n){ return 0;}
	double norm_inf=std::abs(x[0]);
	for(int i=1;i<n;i++){
		double temp=std::abs(x[i]);
		norm_inf=(norm_inf > temp)?norm_inf : temp;
		//norm_inf=(norm_inf > std::abs(x[i]))? norm_inf : std::abs(x[i]); depricating as require abs(x[i]) to calculate two times
	}
	return norm_inf;
}
