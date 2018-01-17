#makefile for compiling and running jacobiOMP program
# hprakash@iu.edu

#compiling for GNU 
# and run like ....
# for example for threads=8, row=1000, cols=1000

# set OMP_NUM_THREADS=8
# time ./jacobiOMP.out 1000 1000 ;  

COMPILER=gcc
CFLAG= -fopenmp 

# "make" command will only compile the code
all:
	@$(COMPILER) jacobiOMP.c -o jacobiOMP.out $(CFLAG)

# "make run" command will compile and run the code
#  also do the plotting in gnuplot
run:
	@$(COMPILER) jacobiOMP.c -o jacobiOMP.out $(CFLAG)
	@ ./jacobiOMP.out 100 100
	@ gnuplot plotHeatMap_gnuplot.gpl

# "make clean" will remove the executable. Redirection used to supress error on console	
clean:
	@rm -rf *.out

#also delete result file (not required,when you run the program again it will anyway overwrite the file)	
kleen:
	@rm -rf *.out
	@rm results.txt
	@rm heat_distribution_map.png

