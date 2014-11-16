#include<stdlib.h>		// for malloc
#include<math.h>		// for pow
#include<string.h>		// memset, memcpy
#include <sys/timeb.h>
#include <assert.h>
#include "utils.h"

int* randPerm(int n) {

	int i, *p = malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		p[i] = i;

	for (i = 0; i < n; i++) {
		int j = ((double) rand() / (RAND_MAX + 1.0)) * i;
		p[i] = p[j];
		p[j] = i;
	}
	return p;
}

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


/* ------------------------------------------------------------------------------- */
/*	Given a matrix A, compute the squared-norms of its columns */
/* ------------------------------------------------------------------------------- */
double
residErrorSparse (const SMAT * A, const double *x, const double *b,
                  const double *z)
{
    int m = A->m, n = A->n;
    int *ir = A->row_ptr, *jc = A->col_ind;
    double *s = A->sVal;
    double *Ax = (double *) malloc (m * sizeof (double));
    int i, j, l;
    double nrm2 = 0.0, nrmX = 0.0;
    memset (Ax, 0, m * sizeof (double));
    for (j = 0; j < n; j++)
    {
        nrmX += pow (x[j], 2);
        for (l = jc[j]; l < jc[j + 1]; l++) // Ax += Ax + A(:, j) * x[j]
            Ax[ir[l]] += s[l] * x[j];
    }
    for (i = 0; i < m; i++)
        nrm2 += pow (Ax[i] - b[i] + z[i], 2);
    free (Ax);
    return sqrt (nrm2 / nrmX);
}
/* ------------------------------------------------------------------------------- */
/*	Given a matrix A, x, b computes norm(A * x - b , 2) */
/* ------------------------------------------------------------------------------- */
double
residError (const MAT * A, double *x, const double *b, const double *z)
{    
    double *Ax = (double *) malloc (A->m * sizeof (double));
    memcpy (Ax, z, A->m * sizeof (double)); // Ax = b;
    for (int i = 0; i < A->m; i++)
        Ax[i] -= b[i];
    // Here, Ax = (z - b);
    myDGEMV(A, x, Ax);
    // Now, Ax = A * x - b + z;
    free (Ax);
    return DNRM2 (A->m, Ax, 1) / DNRM2 (A->n, x, 1);
}



/* ------------------------------------------------------------------------------- */
/*	Given a matrix A,                                                              */
/* ------------------------------------------------------------------------------- */
double
stopCriterionSparse (const SMAT * A, double *z)
{

  int n = A->n, m = A->m, j, l, *ir = A->row_ptr, *jc = A->col_ind;
  double *s = A->sVal, val, result;
  double *y = (double *) malloc (n * sizeof (double));

  memset (y, 0, n * sizeof (double));

  for (j = 0; j < n; j++){
    val = 0.0;
    for (l = jc[j]; l < jc[j + 1]; l++)	// val =  < A(:, j) * z>
        val += s[l] * z[ ir[l]];

      y[j] = val;
  }

  result = DNRM2 (n, y, 1) / DNRM2 (m, z, 1);
  free (y);
  return result;
}


/* ------------------------------------------------------------------------------- */
/*	 Stopping criterion for randomized approximate orthogonal projection           */
/* ------------------------------------------------------------------------------- */
double
stopCriterionDense (const MAT * A, double *z)
{

	int i, j, m = A->m, n = A->n;
	double result, val, *y = (double *) malloc (A->n * sizeof (double));

	memset(y, 0.0, n * sizeof(double));

    for( j = 0 ; j < n ; j++){
    	 val = 0.0;
         for (i = 0 ; i < m; i++)
        	 val += A->val[ j * m + i] * z[i];

         y[j] += val;
     }

  // y = A^T * z;
  result = DNRM2 (n, y, 1) / DNRM2 (m, z, 1);
  free (y);

  return result;
}


// Given an m x n matrix A, a n-vector x and an m-vector y, computes
//
// y <- y + A * x
//
void myDGEMV(const MAT* A, const double* x, double* y) {

	int i, j, m = A->m, n = A->n;

	for (j = 0; j < n; j++)
		for (i = 0; i < m; i++)
			y[i] += A->val[j * m + i] * x[j];
}


// Given an m x n sparse matrix A, a n-vector x and an m-vector y, computes
//
// y <- y + A * x
//
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
    double* vector = malloc(size * sizeof(double));

    for (int i = 0; i < size; i++){
        vector[i] = ((double) rand() / (RAND_MAX + 1.0));
    }

    return vector;
}

double lsErrorSparse(const SMAT* A, const double* x, const double* b){
    double error = 0.0;
    double* residVector = malloc(A->m * sizeof(double));

    for (int i = 0 ; i < A->m; i++){
        residVector[i] = - b[i];
    }

    // residVector <- A * x - b
    myDGEMVSparse(A, x, residVector);

    error = DNRM2(A->m, residVector, 1);
    free(residVector);

    return error;


}


double lsError(const MAT* A, const double* x, const double* b){
    double error = 0.0;
    double* residVector = malloc(A->m * sizeof(double));

    for (int i = 0 ; i < A->m; i++){
        residVector[i] = - b[i];
    }

    // residVector <- A * x - b
    myDGEMV(A, x, residVector);

    error = DNRM2(A->m, residVector, 1);
    free(residVector);

    return error;
}
