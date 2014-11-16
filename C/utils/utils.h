/* 
 * File:   utils.h
 * Author: azo
 *
 * Created on October 30, 2013, 1:46 PM
 */
#ifndef _UTILS_HPP
#define _UTILS_HPP

#include "../matrix/matrix.h"
#include "../matrix/sparseMatrix.h"
#include "../cBlas/cblas.h"



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

// Generate a random permutation of {1,2,...,n}
int* randPerm(int n);

void myDGEMV(const MAT* A, const double* x, double* y);

void myDGEMVSparse(const SMAT* A, const double* x, double* y);



/**
 * Computes norm( A^T * z) / norm(z)
 *
 *
 * @param  A (Input) Dense matrix stored in struct matrix
 * @param  z (Input) Vector
 * @return The Euclidean norm of the vector norm(A' * z) / norm(z)
 */
double stopCriterionDense (const MAT * A, double *z);


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
double stopCriterionSparse (const SMAT * A, double *z);


/**
 * Generate a random Gaussian vector
 *
 */
double* gaussianVector(int size);

double lsErrorSparse(const SMAT* A, const double* x, const double* b);
double lsError(const MAT* A, const double* x, const double* b);



#endif  /* UTILS_H */

