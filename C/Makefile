CC=gcc
CFLAGS=-c -Wall -O2 

all: REK

REK: main.o matrix.o sparseMatrix.o aliasSampler.o utils.o cBLAS.o REKBLAS.o
	gcc matrix.o sparseMatrix.o aliasSampler.o utils.o cBLAS.o REKBLAS.o main.o -o REK

main.o: main.c
	$(CC) $(CFLAGS) main.c

REKBLAS.o: algorithms/REK/REKBLAS.c
	$(CC) $(CFLAGS)  algorithms/REK/REKBLAS.c

matrix.o: matrix/matrix.c
	$(CC) $(CFLAGS) matrix/matrix.c

sparseMatrix.o: matrix/sparseMatrix.c
	$(CC) $(CFLAGS) matrix/sparseMatrix.c

aliasSampler.o: sampler/aliasSampler.c
	$(CC) $(CFLAGS) sampler/aliasSampler.c

utils.o: utils/utils.c
	$(CC) $(CFLAGS) utils/utils.c

cBLAS.o: cBLAS/cBLAS.c
	$(CC) $(CFLAGS) cBLAS/cBLAS.c

clean:
	rm -rf *.o REK
