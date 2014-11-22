/* 
 * File:   utils.h
 * Author: Anastasios Zouzias
 *
 * Created on October 30, 2013, 1:46 PM
 */
#ifndef _UTILS_HPP
#define _UTILS_HPP

#include "../matrix/matrix.h"
#include "../matrix/sparseMatrix.h"
#include "../cBlas/cblas.h"

// Wall time in linux
double wtime();

/**
 * Computes norm( A * x - (b - z), 2)
 *
 *
 * @param  A (Input) Dense matrix stored in struct matrix 
 * @param  x (Input) Vector
 * @param  b (Input) Vector
 * @param  z (Input) Vector
 * @return The Euclidean norm of the vector A * x - (b - z)
 */
double residError(const MAT * A, double *x, const double *b, const double *z);

/**
 * Computes norm( A * x - (b - z), 2)
 *
 *
 * @param  A (Input) Sparse matrix stored in struct sparseMat 
 * @param  x (Input) Vector
 * @param  b (Input) Vector
 * @param  z (Input) Vector
 * @return The Euclidean norm of the vector A * x - (b - z)
 */
double residErrorSparse(const SMAT * A, const double *x, const double *b,
		const double *z);


/**
 * Computes y = y + A * x. Overwrites the result on vector y.
 *
 * @param  A (Input) Dense matrix
 * @param  x (Input) Vector
 * @param  y (Input/Output) Vector
 */
void myDGEMV(const MAT* A, const double* x, double* y);

/**
 * Computes y = y + A * x. Overwrites the result on vector y.
 *
 * @param  A (Input) Sparse matrix
 * @param  x (Input) Vector
 * @param  y (Input/Output) Vector
 */
void myDGEMVSparse(const SMAT* A, const double* x, double* y);

/**
 * Generate a random Gaussian vector
 *
 * @param size (Input) Size of vector
 * @return A Gaussian random vector of size "size" (allocate space)
 */
double* gaussianVector(int size);

/**
 * Computes the least-squares error of the ||Ax - b ||_2 with A sparse
 
 * @param  A (Input) Sparse matrix of size m x n
 * @param  x (Input) Unknown vector of size n
 * @param  b (Input) Right hand side vector of size m
 * @return The Euclidean norm of the vector A * x - b
 *
 */
double lsErrorSparse(const SMAT* A, const double* x, const double* b);

/**
 * Computes the least-squares error of the ||Ax - b ||_2
 *
 * @param  A (Input) Dense m x n matrix 
 * @param  x (Input) Unknown vector of size n
 * @param  b (Input) Right hand side vector of size m
 * @return The Euclidean norm of the vector A * x - b
*
 */
double lsError(const MAT* A, const double* x, const double* b);

#endif  /* UTILS_H */

