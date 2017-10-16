/* 
 * Hitender Prakash 
 * Header file for functions: norm1, norm2 and norminf
 */
#include <string>
#include <sstream>
#include <iomanip>

#ifndef NORMS_H
#define NORMS_H

double norm1(int n, double *x);
double norm2(int n, double *x);
double norminf(int n, double *x);
double elapsedtime (void);

//static __inline__ unsigned long long rdtsc(void);//not using
//double cpuClockRate(); //not using 

//Custom to_string implementation for getting double value with 17 decimal places precision 
//Reference: https://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-g-mingw 
namespace norms
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << std::fixed << std::setprecision(17)<< n ;
        return stm.str() ;
    }
}

#endif
