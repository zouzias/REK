#include<stdlib.h>		// for malloc
#include<math.h>		// for pow
#include<string.h>		// memset, memcpy
#include <sys/timeb.h>
#include <assert.h>
#include "utils.h"

/* Get time */
double wtime() {
    struct timeb T;
    static time_t time_diff;
    static time_t mill_diff;

    double dt;
    (void) ftime(&T);

    time_diff = T.time;
    mill_diff = T.millitm;

    dt = ((double) time_diff) + (1e-3) * ((double) mill_diff);

    return dt;
}

double residErrorSparse (const SMAT * A, const double *x, const double *b, const double *z){
    int m = A->m, n = A->n;
    int *ir = A->row_ptr, *jc = A->col_ind;
    double *s = A->sVal;
    double *Ax = (double *) malloc (m * sizeof (double));
    int i, j, l;
    double nrm2 = 0.0, nrmX = 0.0;
    memset (Ax, 0, m * sizeof (double));
    for (j = 0; j < n; j++){
        nrmX += pow (x[j], 2);
        for (l = jc[j]; l < jc[j + 1]; l++){ // Ax += Ax + A(:, j) * x[j]
            Ax[ir[l]] += s[l] * x[j];
        }
    }

    for (i = 0; i < m; i++){
        nrm2 += pow (Ax[i] - b[i] + z[i], 2);
    }

    free(Ax);

    return sqrt (nrm2 / nrmX);
}

double residError (const MAT * A, double *x, const double *b, const double *z){
    int i;
    double *Ax = (double *) malloc (A->m * sizeof (double));
    memcpy (Ax, z, A->m * sizeof (double)); // Ax = b;

    for (i = 0; i < A->m; i++)
        Ax[i] -= b[i];

    // Here, Ax = (z - b);
    myDGEMV(A, x, Ax);

    // Now, Ax = A * x - b + z;
    free (Ax);

    return DNRM2 (A->m, Ax, 1) / DNRM2 (A->n, x, 1);
}

void myDGEMV(const MAT* A, const double* x, double* y) {
    int i, j, m = A->m, n = A->n;

    for (j = 0; j < n; j++)
        for (i = 0; i < m; i++)
            y[i] += A->val[j * m + i] * x[j];
}

void myDGEMVSparse(const SMAT* A, const double* x, double* y) {
    int n = A->n, j, l, *ir = A->row_ptr, *jc = A->col_ind;
    double *s = A->sVal;

    for (j = 0; j < n; j++){
        for (l = jc[j]; l < jc[j + 1]; l++){
            y[ir[l]] += s[l] * x[j];
        }
    }
}


double* gaussianVector(int size){
    int i;
    double* vector = (double*) malloc(size * sizeof(double));

    for (i = 0; i < size; i++){
        vector[i] = ((double) rand() / (RAND_MAX + 1.0));
    }

    return vector;
}

double lsErrorSparse(const SMAT* A, const double* x, const double* b){
    int i;
    double error = 0.0;
    double* residVector = (double*) malloc(A->m * sizeof(double));

    for (i = 0 ; i < A->m; i++){
        residVector[i] = - b[i];
    }

    // residVector <- A * x - b
    myDGEMVSparse(A, x, residVector);

    error = DNRM2(A->m, residVector, 1);
    free(residVector);

    return error;
}

double lsError(const MAT* A, const double* x, const double* b){
    int i;
    double error = 0.0;
    double* residVector = (double*) malloc(A->m * sizeof(double));

    for (i = 0 ; i < A->m; i++){
        residVector[i] = - b[i];
    }

    // residVector <- A * x - b
    myDGEMV(A, x, residVector);

    error = DNRM2(A->m, residVector, 1);
    free(residVector);

    return error;
}
