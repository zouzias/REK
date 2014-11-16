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
#include "src/algorithms/QR/approxQR.h"
#include "src/matrix/sparseMatrix.h"
#include "src/matrix/matrix.h"
#include "src/utils/utils.h"

int main() {
    // Dimensions of matrix A (m x n).
    size_t m = 5000, n = 200;

    // Maximum number of iterations
    size_t MAXITERS = 200;

    /* initialize random seed */
    srand(time(NULL));

    // Allocating space for matrix Q of [Q, R] = QR(A)
    double *Q = (double *) malloc(m * n * sizeof (double));

    if (1) { // Input matrix is sparse (REK_sparse)

        SMAT *A = fillSparseMat(m, n, 0.25);
        printf("--->Randomized Orthonormalizer for sparse matrix.\n");
        approxSparseQRS(A, Q, 10e-5);
        freeSMAT(A);
    } else {// Input matrix is dense

        printf("--->Randomized Orthonormalizer for dense matrix.\n");
        MAT *A = fillRandomEntries(m, n);
        approxDenseQR(A, Q, 10e-5);
        freeMAT(A);
    }

    printf("--->Successfully completed<---\n");
    free(Q);

    return 0;
};


