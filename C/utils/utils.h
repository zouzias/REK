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

void myDGEMV(const MAT* A, const double* x, double* y);

void myDGEMVSparse(const SMAT* A, const double* x, double* y);

/**
 * Generate a random Gaussian vector
 *
 * @param size (Input) Size of vector
 * @return A Gaussian random vector of size "size" (allocate space)
 */
double* gaussianVector(int size);

/**
 * Computes the least-squares error of the ||Ax - b ||_2
 * A is sparse
 *
 */
double lsErrorSparse(const SMAT* A, const double* x, const double* b);

/**
 * Computes the least-squares error of the ||Ax - b ||_2
 *
 */
double lsError(const MAT* A, const double* x, const double* b);

#endif  /* UTILS_H */

