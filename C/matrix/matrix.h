/*
 * matrix.h
 *
 *  Created on: Jul 12, 2013
 *      Author: azo
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>		// for malloc
#include <stddef.h>
#include <string.h>		// memset, memcpy
#include"../cBLAS/cblas.h"

/**
 * A two-dimensional dense matrix struct
 *
 * Elements are stored in a column-wise ordering in 1-dimensional array
 */
struct matrix {
	int m; /*!< Number of rows */
	int n; /*!< Number of columns */
	double *val; /*!< Array of matrix entries */
};

typedef struct matrix MAT;

/**
 * Destructor for MAT struct
 *
 *
 * @param  A (Input) Matrix given in a "struct matrix".
 * @return none
 */
void freeMAT(MAT * A);

/**
 * Create matrix transpose of dense A
 *
 *
 * @param  A (Input) Matrix given in a "struct matrix".
 * @return A transposed stored in "struct matrix"
 */
MAT *createTransp(const MAT * A);

// Permute the column of A according to perm
void permuteCols(MAT* A, int* perm);

/**
 * Compute the square column norms of input dense A. Output stored in prob.
 *
 *
 * @param  A (Input) Dense matrix stored as struct matrix
 * @param  prob (Output) Vector containing column norms squared
 * @return none
 */
void computeColNorms(const MAT * A, double *prob);

MAT* fillRandomEntries(int m, int n);

void printMatrix(const MAT* A);

#endif /* MATRIX_H_ */
