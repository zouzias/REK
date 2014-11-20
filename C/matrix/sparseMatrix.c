/*
 * sparseMatrix.c
 *
 *  Created on: Jul 12, 2013
 *      Author: Anastasios Zouzias
 */

#include "sparseMatrix.h"

/**
 * Frees a sprarse matrix structure
 */
void freeSMAT(SMAT * A) {
    free(A->row_ptr);
    free(A->col_ind);
    free(A->sVal);
    free(A);
}

SMAT * createRowCompressed(const SMAT * A) {
    int j, l, m = A->m, n = A->n, *ir = A->row_ptr, *jc = A->col_ind;
    double *s = A->sVal;
    double nnz = jc[n];
    SMAT *Atransp = (SMAT *) malloc(sizeof(SMAT));
    Atransp->m = n;
    Atransp->n = m;
    
    Atransp->row_ptr = (int *) malloc((m + 1) * sizeof(int));
    Atransp->col_ind = (int *) malloc(nnz * sizeof(int));
    Atransp->sVal = (double *) malloc(nnz * sizeof(double));
    
    memset(Atransp->row_ptr, 0, (m + 1) * sizeof(int));
    
    /*------------------------------------------------------------------
     // Copy array from compressed column sparse (CCS) format to compressed
     // row sparse (CRS) format
     ------------------------------------------------------------------*/
    for (j = 0; j < n; j++){
        for (l = jc[j]; l < jc[j + 1]; l++){
            Atransp->row_ptr[ir[l] + 1]++;
        }
    }
    
    // Fill-in the row_ptr array
    for (l = 1; l < m + 1; l++){
        Atransp->row_ptr[l] = Atransp->row_ptr[l] + Atransp->row_ptr[l - 1];
    }
    
    assert(Atransp->row_ptr[m] == nnz);
    
    int *cur = (int *) malloc(m * sizeof(int));
    memset(cur, 0, m * sizeof(int));
    
    for (j = 0; j < n; j++) {
        for (l = jc[j]; l < jc[j + 1]; l++) {
            Atransp->sVal[Atransp->row_ptr[ir[l]] + cur[ir[l]]] = s[l];
            Atransp->col_ind[Atransp->row_ptr[ir[l]] + cur[ir[l]]] = j;
            cur[ir[l]]++;
        }
    }
    
    free(cur);
    return Atransp;
}

inline void computeRowNorms(const SMAT * A, double *prob) {
    
    int m = A->m, n = A->n, l, j, k;
    int *ir = A->row_ptr, *jc = A->col_ind;
    double *s = A->sVal;
    
    memset(prob, 0, m * sizeof(double));
    for (j = 0; j < n; j++){
        for (l = jc[j], k = jc[j + 1]; l < k; l++){
            prob[ir[l]] = prob[ir[l]] + pow(s[l], 2);
        }
    }
}

inline void computeColNormsSparse(const SMAT * A, double *prob) {
    int n = A->n, *jc = A->col_ind, l, j, k;
    double *s = A->sVal;
    
    memset(prob, 0, n * sizeof(double));
    for (j = 0; j < n; j++){
        for (l = jc[j], k = jc[j + 1]; l < k; l++){
            prob[j] = prob[j] + pow(s[l], 2);
        }
    }
}

SMAT* fillSparseMat(int m, int n, double rowDensity) {
    SMAT *A = (SMAT *) malloc(sizeof(SMAT));
    int i, j, cnt = 0;
    double MAX_NUM = 100;
    
    assert(rowDensity < 1 && rowDensity > 0);
    int nnz = ceil(rowDensity * m) * n;
    A->m = m;
    A->n = n;
    
    A->row_ptr = (int *) malloc(nnz * sizeof(int));
    A->col_ind = (int *) malloc((n + 1) * sizeof(int));
    A->sVal = (double *) malloc(nnz * sizeof(double));
    
    A->col_ind[0] = 0;
    for (j = 0; j < n; j++) {
        for (i = 0; i < m; i++) {
            if (((double) rand() / (RAND_MAX + 1.0)) < rowDensity && cnt < nnz) {
                (A->row_ptr)[cnt] = i;
                (A->sVal)[cnt] = ((double) rand() / (RAND_MAX + 1.0)) * MAX_NUM;
                cnt++;
            }
        }
        A->col_ind[j + 1] = cnt;
    }
    
    return A;
}
