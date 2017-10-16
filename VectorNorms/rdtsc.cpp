#include <time.h>
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

//This method finds the number of rdtsc based counts in 1 second
//For measuring an event, call the rdtsc() before and after the event
//divide the difference by cpuClockRate() and that gives the time for that event
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

