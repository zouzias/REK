/*
 * matrix.c
 *
 * Implementation of a 2D-matrix
 *
 *  Created on: Jul 12, 2013
 *      Author: Anastasios Zouzias
 */

#include "matrix.h"

void freeMAT(MAT * A) {
    free(A->val);
    free(A);
}

/* Create A^T (A transpose) of dense matrix */
MAT * createTransp(const MAT * A) {
    
    int i, j, m = A->m, n = A->n;
    MAT *Atransp = (MAT *) malloc(sizeof(MAT));
    
    Atransp->m = n;
    Atransp->n = m;
    Atransp->val = (double *) malloc(m * n * sizeof(double));
    
    for (j = 0; j < n; j++){
        for (i = 0; i < m; i++){
            Atransp->val[j + i * n] = A->val[i + j * m];
        }
    }
    
    return Atransp;
}

/* ------------------------------------------------------------------------------- */
/*	 Given a matrix A, compute the squared-norms of its columns                    */
/* ------------------------------------------------------------------------------- */
//
inline void computeColNorms(const MAT * A, double *prob) {
    int n = A->n, j, m = A->m;
    
    memset(prob, 0, n * sizeof(double));
    for (j = 0; j < n; j++) {
        prob[j] = cblas_dnrm2(m, (A->val + j * A->m), 1);
        prob[j] = pow(prob[j], 2);
    }
}

MAT* fillRandomEntries(int m, int n) {
    int i, j;
    double MAX_NUM = 100;
    
    MAT *A = malloc(sizeof(MAT));
    A->m = m;
    A->n = n;
    A->val = (double *) malloc(m * n * sizeof(double));
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            (A->val)[j * m + i] = ((double) rand() / (RAND_MAX + 1.0)) * MAX_NUM;
    
    return A;
}

void printMatrix(const MAT* A) {
    int i, j, m = A->m, n = A->n;
    
    printf("# of rows: %d\n", m);
    printf("# of cols: %d\n", n);
    
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++){
            printf("A[%d,%d] = %.3f  ", i, j, A->val[j * m + i]);
        }
        
        printf("\n");
    }
    
}


