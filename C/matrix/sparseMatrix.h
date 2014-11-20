/* 
 * File:   sparseMatrix.h
 * Author: Anastasios Zouzias
 *
 * Created on October 30, 2013, 1:54 PM
 */
#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_

#include<stdio.h>
#include<stdlib.h>		// malloc
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include<string.h>		// memset, memcpy

/**
 * A two-dimensional sparse matrix struct.
 *
 * It uses the compressed column sparse format (see netlib.org for details)
 */
struct sparseMat {
	int m; /*!< Number of rows   */
	int n; /*!< Number of columns */
	int *row_ptr, *col_ind; /*!< Row index and column pointer indices */
	double *sVal; /*!< Non-zero entries */
};

typedef struct sparseMat SMAT;

/**
 * Store matrix in compressed row sparse format
 *
 * Input matrix A is stored in compressed column sparse format, output is stored in compressed row sparse format
 *
 * @param  A (Input) matrix stored in compressed colunm sparse format
 * @return Output matrix is stored in compressed row sparse format
 */
SMAT *createRowCompressed(const SMAT * A);

/**
 * Destructor for SMAT struct
 *
 *
 * @param  A (Input) Sparse matrix in strcut sparseMat
 * @return none
 */
void freeSMAT(SMAT * A);

/**
 * Compute the square row norms of input sparse A. Output stored in prob.
 *
 *
 * @param  A (Input) Sparse matrix stored as struct sparseMat
 * @param  prob (Output) Vector containing square row norms
 * @return none
 */
void computeRowNorms(const SMAT * A, double *prob);

/**
 * Compute the square column norms of input sparse A. Output stored in prob.
 *
 *
 * @param  A (Input) Sparse matrix stored as struct sparseMat.
 * @param  prob (Output) Vector containing sparse column norms.
 * @return none
 */
void computeColNormsSparse(const SMAT * A, double *prob);

/**
 * Generates an m x n sparse random Gaussian matrix with density. Non-zero entries are selected randomly.
 *
 * @param  m (Input) Number of rows.
 * @param  n (Input) Number of columns.
 * @param  density (Input) Fraction of non-zero random entries.
 * @return  A sparse matrix stored as struct sparseMat.
 */
SMAT* fillSparseMat(int m, int n, double density);

#endif /* SPARSEMATRIX_H_ */

