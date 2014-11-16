/*
 * This file provides an implementation of the algorithm in [1].
 *
 * References :
 * [1] - Randomized and Parallel Vector Orthonormalization
 *       Anastasios Zouzias
 *
 *
 * Author      : Anastasios Zouzias
 * Affiliation : University of Toronto
 * Email       : zouzias@cs.toronto.edu
 * Website     : http://www.cs.toronto.edu/~zouzias/
 * Copyright (C) 2012, Anastasios Zouzias
 *
 * September 2012; Last revision: 5-September-2012
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stddef.h>
#include "algorithms/REK/REKBlas.h"
#include "matrix/sparseMatrix.h"
#include "matrix/matrix.h"
#include "utils/utils.h"

int main() {
    // Dimensions of matrix A (m x n).
    int m = 5000, n = 200;

    // Maximum number of iterations
    double TOL = 10e-5;

    // Sparsity of sparse matrix
   double sparsity = 0.25;

    /* initialize random seed */
    srand(time(NULL));

    // Allocating space for unknown vector x Ax = b
    double *xls = gaussianVector(n);
    double* b = (double*) malloc( m * sizeof(double));
    double* x = (double*) malloc( n * sizeof(double));
    memset (x, 0, n * sizeof (double));
    
    // LS Error
    double error = 0.0;
    
    // Input matrix is sparse (REK_sparse)

        SMAT *As = fillSparseMat(m, n, sparsity);
        
        myDGEMVSparse(As,xls, b);

        printf("--->REK for sparse (%dx%d)-matrix with sparsity %f.\n", m, n, sparsity);
        REKBLAS_Sparse (As, x, b, TOL);
        error = lsErrorSparse(As, x, b);
        freeSMAT(As);

    printf(" LS error is %e\n", error);

    // Input matrix is dense

        printf("--->REK for dense (%dx%d)-matrix.\n", m, n);
        MAT *A = fillRandomEntries(m, n);
        
	memset (b, 0, m * sizeof (double));
	memset (x, 0, n * sizeof (double));
        myDGEMV(A,xls, b);
        REKBLAS_Dense(A, x, b, TOL);
        error = lsError(A, x, b);
        freeMAT(A);
        
    printf(" LS error is %e\n", error);

    free(xls);
    free(x);
    free(b);

    return 0;
};


