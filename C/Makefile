CC=gcc
CFLAGS=-c -Wall -O3 
SUBDIRS= src . tests
CHECK_LIBS=/usr/local/Cellar/check/0.9.14/lib/

all: REK

test: REK tests/check_test.c
	export CK_DEFAULT_TIMEOUT=100
	gcc -c tests/check_test.c
	gcc check_test.o matrix.o sparseMatrix.o aliasSampler.o utils.o cBLAS.o REKBLAS.o -L${CHECK_LIBS} -lcheck -o test
	./test

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
