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
	while(getline(infile, line)){
		istringstream isobj(line);
		if(!(isobj >> nstart >>nstride >> nend >> nflops)){break;}
	}
	infile.close();
	//cout<<"\nnstart: "<<nstart <<" nend: "<<nend<<" nstride: "<<nstride<<" nflops: "<<nflops;
	
	vector<string> result_str;
	//double clock_rate=cpuClockRate();
	double start;
	double finish;
	double elapsed;

	int loopCount=0;
	for(loopCount=nstart;loopCount<=nend;loopCount+=nstride){
		vector<double> x(loopCount,0);
		for(int i=0;i<loopCount;i++){
			x[i]=rand();
		}
		//measure norm1
		int repCount;		
		repCount=(nflops/(2*loopCount));
		int temp=repCount;
		start=elapsedtime();
		//start=rdtsc();
		while(temp>=0){
			double norm_1=norm1(loopCount,x);
			temp--;
		}
		finish=elapsedtime();
		//finish=rdtsc();
		elapsed=(finish-start);
		result_str.push_back(norms::to_string(loopCount)+ "\t"+ norms::to_string((double)elapsed/repCount)+"\t"+norms::to_string(repCount)+"\t1\n");	
		//result_str.push_back(norms::to_string(loopCount)+ "\t" + norms::to_string(elapsed)+"\t"+ norms::to_string((double)elapsed/repCount)+"\t"+norms::to_string(repCount)+"\t1\n");
		//cout<<"\nTime for norm1: "<<n1_t;
		//================================
		
		//measure norm2
		repCount=(nflops/(2*loopCount+1));
		temp= repCount;
		start=elapsedtime();
		while(temp>=0){
			double norm_2=norm1(loopCount,x);
			temp--;
		}
		finish=elapsedtime();
		elapsed=(finish-start);
		result_str.push_back(norms::to_string(loopCount)+ "\t" + norms::to_string((double)elapsed/repCount)+"\t"+ norms::to_string(repCount)+"\t2\n");
		//result_str.push_back(norms::to_string(loopCount)+ "\t" + norms::to_string(elapsed)+"\t" + norms::to_string((double)elapsed/repCount)+"\t"+ norms::to_string(repCount)+"\t2\n");
		//cout<<"\nTime for norm2: "<<n2_t;
		//================================
		
		//measure norm1
		repCount=(nflops/(2*loopCount));
		temp=(long)repCount;
		start=elapsedtime();
		while(temp>=0){
			double norm_inf=norminf(loopCount,x);
			temp--;
		}
		finish=elapsedtime();
		elapsed=(finish-start);
		result_str.push_back(norms::to_string(loopCount)+ "\t" +  norms::to_string((double)elapsed/repCount)+"\t"+ norms::to_string(repCount)+"\t3\n");
		//result_str.push_back(norms::to_string(loopCount)+ "\t" + norms::to_string(elapsed)+"\t" +  norms::to_string((double)elapsed/repCount)+"\t"+ norms::to_string(repCount)+"\t3\n");
		//cout<<"\nTime for norm inf: "<<ninf_t;
		//================================
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
