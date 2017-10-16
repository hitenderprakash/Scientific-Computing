/*
 * Hitender Prakash
 * Date: October 12, 2017
 * Program to calculate vector norms 
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include "norms.h"
#include <vector>

using namespace std;
int main () {

	int nstart=0;
	int nend=0;
	int nstride=0;
	double nflops=0.0;

	ifstream infile;
	infile.open("sizes");
	string line;
	if(!infile){cout<<"\nError in reading input file: sizez, make sure file exists in current directory. Exiting !";exit(0);}
	else if(infile.peek() == std::ifstream::traits_type::eof()){cout<<"\nError in reading input file: sizez, file is empty. Exiting !";exit(0);} 
	while(getline(infile, line)){
		istringstream isobj(line);
		if(!(isobj >> nstart >>nstride >> nend >> nflops)){break;}
	}
	infile.close();
	//cout<<"\nnstart: "<<nstart <<" nend: "<<nend<<" nstride: "<<nstride<<" nflops: "<<nflops;
	
	vector<string> result_str; //to store result strings
	double start;
	double finish;
	double elapsed;

	int loopCount=0;
	for(loopCount=nstart;loopCount<=nend;loopCount+=nstride){
		//vector<double> x(loopCount,0);
		double *x=new double[loopCount];
		if(!x){cout<<"\nError: Memory allocation for array failed ! Exiting..";exit(0);}
		for(int i=0;i<loopCount;i++){
			x[i]=rand();
			//x[i]=1.0;
		}
		//===========measure norm1============
		int repCount;		
		repCount=nflops/(2*loopCount);
		int temp=repCount;
		start=elapsedtime();
		//start=rdtsc();
		while(temp>=0){
			double norm_1=norm1(loopCount,x);
			//if(temp==0){cout<<"\nNorm1: "<<norm_1;}
			temp--;
		}
		finish=elapsedtime();
		//finish=rdtsc();
		elapsed=(finish-start);
		result_str.push_back(norms::to_string(loopCount)+ "\t"+ norms::to_string((double)elapsed/repCount)+"\t"+norms::to_string(repCount)+"\t1\n");	
		//====================================
		
		//==========measure norm2=============
		repCount=nflops/(2*loopCount+1);
		temp= repCount;
		start=elapsedtime();
		while(temp>=0){
			double norm_2=norm2(loopCount,x);
			//if(temp==0){cout<<"\nNorm2: "<<norm_2;}
			temp--;
		}
		finish=elapsedtime();
		elapsed=(finish-start);
		result_str.push_back(norms::to_string(loopCount)+ "\t" + norms::to_string((double)elapsed/repCount)+"\t"+ norms::to_string(repCount)+"\t2\n");
		//===================================
		
		//=========measure norm-inf==========
		repCount=nflops/(2*loopCount);
		temp=(long)repCount;
		start=elapsedtime();
		while(temp>=0){
			double norm_inf=norminf(loopCount,x);
			//if(temp==0){cout<<"\nNorminf: "<<norm_inf;}
			temp--;
		}
		finish=elapsedtime();
		elapsed=(finish-start);
		result_str.push_back(norms::to_string(loopCount)+ "\t" +  norms::to_string((double)elapsed/repCount)+"\t"+ norms::to_string(repCount)+"\t3\n");
		//===================================
		//free the memory
		delete(x);
	}
	
	//write result file
	ofstream outfile;
	outfile.open("results");
	for(int i=0;i<result_str.size();i++){
		outfile<<result_str[i];
	}
	outfile.close();
    return 0;
}
