/*
 * Hitender Prakash
 * Date: October 12, 2017
 * Program to calculate vector norms 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "norms.h"

double norm2(int n, double *x);
int main () {

	int nstart=0;
	int nend=0;
	int nstride=0;
	double nflops=0.0;
	
	//read file	
	char filename[]="sizes"; //file should be present in the current directory
	FILE *file = fopen ( filename, "r" );
	if ( file != NULL ){
       char line [100];
       while(fgets(line,sizeof(line),file)!=NULL){
          char *tok;
          int tok_num=0;
          tok=strtok(line," ");         
          while(tok!=NULL){
			 tok_num++;		 
			 if(tok_num==1){ nstart=atoi(tok);} //read nstart		 
			 else if(tok_num==2){nstride=atoi(tok);} //read nstride		 
			 else if(tok_num==3){nend=atoi(tok);} //read nend
			 else if(tok_num==4){nflops=atof(tok);} //read nflops
			 tok=strtok (NULL, " ");
		  }

       }
       fclose(file);
    }
    else
    {
       printf("\nNOT ABLE TO READ FILE. PLEASE CHECK IF FILE EXISTS");
       printf("\nPLEASE KEEP BOTH, EXECUTABLE AND DEPENDENT MTX FILES IN CURRENT WORKING DIRECTORY");
       printf("\nEXITING NOW...");
       exit(0);
      
    }

	printf("\nnstart: %d  nend: %d nstride: %d nflops: %e",nstart,nend,nstride,nflops);
	int n=10;
	double *x=0;
	x=(double *)malloc(n*sizeof(double));
	int i;
	for(i=0;i<10;i++){
		x[i]=i-5;
	}
	printf("\nNorm1: %lf",norm1(10,x));
	printf("\nNorm2: %lf",norm2(10,x));
	printf("\nNorm inf: %lf",norminf(10,x));
	printf("\n");
    return 0;
}
