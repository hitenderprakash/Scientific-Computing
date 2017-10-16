/* 
 * Hitender Prakash 
 * Header file for functions: norm1, norm2 and norminf
 */
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#ifndef NORMS_H
#define NORMS_H

double norm1(int n, std::vector<double> &x);
double norm2(int n, std::vector<double> &x);
double norminf(int n, std::vector<double> &x);

//Code for using RDTSC for getting CPU clock rate
/* rdtsc() function
 * input: NULL
 * output: returns the processor time stamp counter
 * used to measure the active cycles of processor for a job
 * The following code has been taken from:
 * http://www.unix.com/programming/81639-rdtsc-use-c.html
 */
#if defined(__i386__)
// For x86 machine
static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}
//for x64 machine
#elif defined(__x86_64__)
static __inline__ unsigned long long rdtsc(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}
#elif defined(__powerpc__)
static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int result=0;
  unsigned long int upper, lower,tmp;
  __asm__ volatile(
                "0:                  \n"
                "\tmftbu   %0           \n"
                "\tmftb    %1           \n"
                "\tmftbu   %2           \n"
                "\tcmpw    %2,%0        \n"
                "\tbne     0b         \n"
                : "=r"(upper),"=r"(lower),"=r"(tmp)
                );
  result = upper;
  result = result<<32;
  result = result|lower;
  return(result);
}
#endif 
//http://www.unix.com/programming/81639-rdtsc-use-c.html

double cpuClockRate(){
	double init=time(NULL);
	while (init==time(NULL)){}
	double start=rdtsc();
	init=time(NULL);
	while (init==time(NULL)){}
	double end=rdtsc();
	double clockRate=end-start;
	return clockRate;
}


//if std::to_string does not work
// reference: https://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-g-mingw 
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
