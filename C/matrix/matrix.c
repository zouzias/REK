/*
 * matrix.c
 *
 *  Created on: Jul 12, 2013
 *      Author: azo
 */

#include "matrix.h"

void freeMAT(MAT * A) {
	free(A->val);
	free(A);
}

/* Create A^T of dense matrix */
MAT *
createTransp(const MAT * A) {

	int i, j;
	MAT *Atransp = (MAT *) malloc(sizeof(MAT));

	Atransp->m = A->n;
	Atransp->n = A->m;
	Atransp->val = (double *) malloc(A->m * A->n * sizeof(double));

	for (j = 0; j < A->n; j++)
		for (i = 0; i < A->m; i++)
			Atransp->val[j + i * (A->n)] = A->val[i + j * A->m];

	return Atransp;
}

/* ------------------------------------------------------------------------------- */
/*	 Given a matrix A, compute the squared-norms of its columns                    */
/* ------------------------------------------------------------------------------- */
//
inline void computeColNorms(const MAT * A, double *prob) {
	int n = A->n, j, m = A->m, incx = 1;

	memset(prob, 0, n * sizeof(double));
	for (j = 0; j < n; j++) {
		prob[j] = cblas_dnrm2(m, (A->val + j * A->m), incx);
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
			(A->val)[j * m + i] = ((double) rand() / (RAND_MAX + 1.0))
					* MAX_NUM;

	return A;
}

void printMatrix(const MAT* A) {
	int i, j, m = A->m, n = A->n;

	printf("# of rows: %d\n", m);
	printf("# of cols: %d\n", n);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("A[%d,%d] = %.3f  ", i, j, A->val[j * m + i]);

		printf("\n");
	}

}

void permuteCols(MAT* A, int* perm) {

	int j, m = A->m, n = A->n;
	MAT *B = malloc(sizeof(MAT));
	B->m = m;
	B->n = n;
	B->val = (double *) malloc(m * n * sizeof(double));

	for (j = 0; j < n; j++)
		memcpy((B->val + j * m), (A->val + perm[j] * m), m * sizeof(double));

	memcpy(A->val, B->val, m * n * sizeof(double));

	freeMAT(B);
}



