#makefile 
COMPILER=gcc
CFLAG= -lm

# "make" command will only compile the code
all:
	@$(COMPILER) norm1.c -c
	@$(COMPILER) norm2.c -c
	@$(COMPILER) norminf.c -c
	@$(COMPILER) main.c -c
	@$(COMPILER) main.o norm1.o norm2.o norminf.o -o main.out $(CFLAG)


# "make run" command will compile ad run the code
# only one file will compile and run @#@ represented commented out lines and will not print to screen
run:
	@$(COMPILER) norm1.c -c
	@$(COMPILER) norm2.c -c
	@$(COMPILER) norminf.c -c
	@$(COMPILER) main.c -c
	@$(COMPILER) main.o norm1.o norm2.o norminf.o -o main.out $(CFLAG)
	@ ./main.out

# "make clean" will remove the executable. Redirection used to supress error on console	
clean:
	@rm -rf *.out
	@rm -rf *.o

