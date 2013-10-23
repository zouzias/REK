#ifndef _REKBLAS_H
#define _REKBLAS_H

#include "types.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "blas.h"
#include <time.h>

#define DDOT ddot_
#define DAXPY daxpy_

#include "AliasSampler.h"
#include "utils.h"

/*!< REK periodically checks for convergence after BLOCKSIZE iterations */
extern unsigned int BLOCKSIZE;

/*!< Maximum number of iterations */
extern unsigned int MAXITERS;


/**
 * Randomized Extended Kaczmarz method for dense input matrices
 *
 * This method implements the randomized extended Kaczmarz method as described in [1] for the case
 * of dense input matrix A. This method uses BLAS level-1 methods (i.e., ddot, saxpy, nrm2)
 *
 * CAUTION : You can to link with cblas library, i.e., -lcblas
 *
 * [1] - Randomized Extended Kaczmarz for Solving Least-Squares. Anastasios Zouzias and Nikolaos Freris (http://arxiv.org/abs/1205.5770)
 *
 *
 * @param  x (Output) The minimum Euclidean norm least squares vector x, i.e., argmin ||Ax -b ||_2
 * @param  A (Input)  An m x n matrix A (struct matrix)
 * @param  b (Input)  Right hand side vector b
 * @param  iters (Input)  Maximum number of iterations
 * @return None
 */
void REKBLAS_Dense (MAT * A, double *x, const double *b, double TOL);

/**
 * Randomized Extended Kaczmarz method for sparse input matrices
 *
 * This method implements the randomized extended Kaczmarz method as described in [1] for the case
 * of dense input matrix A. This method uses BLAS level-1 methods (i.e., ddot, saxpy, nrm2)
 *
 *
 * CAUTION : You can to link with cblas library, i.e., -lcblas
 *
 * [1] - Randomized Extended Kaczmarz for Solving Least-Squares. Anastasios Zouzias and Nikolaos Freris (http://arxiv.org/abs/1205.5770)
 *
 * @param  x   (Output) The minimum Euclidean norm least squares vector x, i.e., argmin ||Ax -b ||_2
 * @param  A   (Input)  An m x n matrix A (stored in compressed column matrix format)
 * @param  b   (Input)  Right hand side vector b
 * @param  TOL (Input)  Tolerance of the algorithm
 * @return See first argument
 */
void REKBLAS_Sparse (const SMAT * A, double *x, const double *b,
		     double TOL);


#endif
