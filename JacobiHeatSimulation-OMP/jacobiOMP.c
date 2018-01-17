#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "rdtsc_timer.h"
#define eps 1e-3
#define maxitr 1000

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define abs(a)   ((a>0)?(a):(-a))

//write a string to a file
void write_to_file(char *message,char *filename, char *file_mode);
//write a matrix to the file
void write_matrix_to_file(double** matrix,int rows, int cols, char *filename, char *file_mode);
//display matrix to console
void displayMatrix(double **matrix, int rows, int cols);

int main(int argc, char *argv[]){
	int i=0;
	int j=0;
	int rows=0;
	int cols=0;//initialize with 0,though these values are taken from command line arguments
	if(argc!=3){
		printf("\nUsage: prog <rows> <cols>\n"); 
		exit(0);
	}
	//read rows and columns from the arguments 
	//c does not support try catch, if user enters garbage it may fail
	rows=atoi(argv[1]);
	cols=atoi(argv[2]);
	
	//check if rows and columns are not zero
	if(!rows || !cols){
		printf("\nError: Rows or Coloumns cannot be 0 ! Exiting...\n");
		exit(0);
	}
	//allocate space for matrix (plate)
	double **plate=0;
	plate = (double **)malloc(rows*sizeof(double*));
	if(!plate){
		printf("\nError: Memory allocation failure ! Exiting...\n");
		exit(0);
	}
	for(i=0;i< rows;i++){
		plate[i]=(double*)malloc(cols*sizeof(double));
		if(!plate[i]){
			printf("\nError: Memory allocation failure ! Exiting...\n");
			exit(0);
		}
	}
	
	//allocate space for copy matrix (plate)
	double **plateCpy=0;
	plateCpy = (double **)malloc(rows*sizeof(double*));
	if(!plateCpy){
		printf("\nError: Memory allocation failure ! Exiting...\n");
		exit(0);
	}
	for(i=0;i< rows;i++){
		plateCpy[i]=(double*)malloc(cols*sizeof(double));
		if(!plateCpy[i]){
			printf("\nError: Memory allocation failure ! Exiting...\n");
			exit(0);
		}
	}
	
	//assign initial values of the temperatures on all coordinates
	//same initial state is applied to the copy of plate matrix as it saves extra copying effort
	for(i=0;i<rows;i++){
		for(j=0; j<cols;j++){
			plate[i][j]=0.0;
			plateCpy[i][j]=0.0;
			if(i==0){
				plate[i][j]=10.0;
				plateCpy[i][j]=10.0;
			}
		}
	}
	
	int steadyStateFlag=0;
	int itr=0;
	double maxdiff=0;
	double old_maxfidd=0;
	//jacobi process starts here
	double clock_rate=cpuClockRate();
	double start=(double)rdtsc();
	while(itr<maxitr){	
		#pragma omp parallel for shared(i) private (j)
		for(i=1;i<rows-1;i++){
			for(j=1;j<cols-1;j++){
				plateCpy[i][j]= (plate[i-1][j]+plate[i+1][j]+plate[i][j-1]+plate[i][j+1])*0.25;
				
				#pragma omp critical
				{
					maxdiff=max(maxdiff, abs(plateCpy[i][j]-plate[i][j]));
				}
			}
		}
		#pragma omp barrier
		
		//temperature on boundry remains fixed so only internal coordinates are copied 
		//between plateCpy to plate
		#pragma omp parallel for shared(i) private (j)
		for(i=1;i<rows-1;i++){
			for(j=1;j<cols-1;j++){
				plate[i][j]=plateCpy[i][j];
			}
		}
		#pragma omp barrier
		itr++;

		if(maxdiff < eps){
			steadyStateFlag = 1;
			break;
		}
	}

	double finish=(double)rdtsc(); 
	double timeStamps_taken=finish - start;
	double timeConsumed=(timeStamps_taken/clock_rate);
	if(steadyStateFlag==1){
		printf("\nPlate state attained steady state");
	}
	else{
		printf("\nMaximum iteration exhausted");
	}
	printf("\nTotal simmulation time: %lf seconds\n",timeConsumed);
	printf("\nFinal state of plate written to file: result.txt\n");
	//write final plate state to file
	write_matrix_to_file(plate,rows,cols,"results.txt", "w+");
	
	//free memory
	for(i=0;i<rows;i++){
		free(plate[i]);
		free(plateCpy[i]);
	}
	free(plate);
	free(plateCpy);
	printf("\n\n");
	return 0;
}

//============================= define functions =======================
/* display matrix to console
 * input:
 * matrix: matrix to be written
 * rows: number of rows in matrix
 * cols: number of columns in matrix
 * Output: void
 */
void displayMatrix(double **matrix, int rows, int cols){
	if(!matrix){return;}
	int i,j;
	for(i=0;i<rows;i++){
		printf("\n");
		for(j=0;j<cols;j++){

			printf("\t%f",matrix[i][j]);
		}
	}
	printf("\n");
}

/* write a matrix data to file
 * input:
 * matrix: matrix to be written
 * rows: number of rows in matrix
 * cols: number of columns
 * filename: file to write
 * file_mode: mode to open the file like create or append
 * Output: void
 */
void write_matrix_to_file(double** matrix,int rows, int cols,char *filename, char *file_mode){
	FILE *fout=fopen(filename,file_mode);
	int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++){
            fprintf(fout,"%lf\t", matrix[i][j]);
        }
        fprintf(fout,"\n");
    }
    fclose(fout);
}
/* write a string to a file
 * input:
 * message: string to write
 * filename: file to write
 * file_mode: mode to open the file like create or append
 * Output: void
 */
void write_to_file(char *message,char *filename, char *file_mode){
	FILE *fout=fopen(filename,file_mode);
	fprintf(fout,"%s",message);
	fclose(fout);
}

//============================= functions definition ends =======================
