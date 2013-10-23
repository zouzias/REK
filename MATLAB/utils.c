#include "mex.h"
#include<stdlib.h>		// for malloc
#include<math.h>		// for pow
#include<string.h>		// memset, memcpy
#include <sys/timeb.h>
#include "blas.h"
#include <assert.h>
#include "REKBLAS.h"

#define DNRM2 dnrm2_
#define DGEMV dgemv_


/* Get time */
double
wtime ()
{
  struct timeb T;

  static time_t time_diff;
  static time_t mill_diff;

  double dt;

  (void) ftime (&T);

  time_diff = T.time;
  mill_diff = T.millitm;

  dt = ((double) time_diff) + (1e-3) * ((double) mill_diff);

  return dt;
}

void
freeMAT (MAT * A)
{
  free (A->val);
  free (A);
}

void
freeSMAT (SMAT * A)
{
  free (A->row_ptr);
  free (A->col_ind);
  free (A->sVal);
  free (A);
}

/* Create A^T of dense matrix */
MAT *
createTransp (const MAT * A)
{

  size_t i, j;
  MAT *Atransp = (MAT *) malloc (sizeof (MAT));

  Atransp->m = A->n;
  Atransp->n = A->m;
  Atransp->val = (double *) malloc (A->m * A->n * sizeof (double));

  // Transpose
  for (j = 0; j < A->n; j++)
    for (i = 0; i < A->m; i++)
      Atransp->val[j + i * (A->n)] = A->val[i + j * A->m];

  return Atransp;
}

/* Create A in compressed row sparse format (assuming input A in compressed column format) */
SMAT *
createRowCompressed (const SMAT * A)
{

  size_t j, l, m = A->m, n = A->n, *ir = A->row_ptr, *jc = A->col_ind;
  double *s = A->sVal;

  SMAT *Atransp = (SMAT *) malloc (sizeof (SMAT));
  Atransp->m = n;
  Atransp->n = m;

  double nnz = jc[n];

  Atransp->row_ptr = (size_t *) malloc ((m + 1) * sizeof (size_t));
  Atransp->col_ind = (size_t *) malloc (nnz * sizeof (size_t));
  Atransp->sVal = (double *) malloc (nnz * sizeof (double));

  memset (Atransp->row_ptr, 0, (m + 1) * sizeof (size_t));

	/*------------------------------------------------------------------
	// Copy array from compressed column sparse (CCS) format to compressed
	// row sparse (CRS) format
	------------------------------------------------------------------*/
  for (j = 0; j < n; j++)
    for (l = jc[j]; l < jc[j + 1]; l++)
      Atransp->row_ptr[ir[l] + 1]++;

  // Fill-in the row_ptr array
  for (l = 1; l < m + 1; l++)
    Atransp->row_ptr[l] = Atransp->row_ptr[l] + Atransp->row_ptr[l - 1];

  assert (Atransp->row_ptr[m] == nnz);

  size_t *cur = (size_t *) malloc (m * sizeof (size_t));
  memset (cur, 0, m * sizeof (size_t));

  for (j = 0; j < n; j++)
    {
      for (l = jc[j]; l < jc[j + 1]; l++)
	{
	  Atransp->sVal[Atransp->row_ptr[ir[l]] + cur[ir[l]]] = s[l];
	  Atransp->col_ind[Atransp->row_ptr[ir[l]] + cur[ir[l]]] = j;
	  cur[ir[l]]++;
	}
    }

  free (cur);

  return Atransp;
}

/* ------------------------------------------------------------------------------- */
/*	Given a matrix A, compute the squared-norms of its columns                 */
/* ------------------------------------------------------------------------------- */
double
residErrorSparse (const SMAT * A, const double *x, const double *b,
		  const double *z)
{

  size_t m = A->m, n = A->n;
  size_t *ir = A->row_ptr, *jc = A->col_ind;
  double *s = A->sVal;

  double *Ax = (double *) malloc (m * sizeof (double));
  int i, j, l;
  double nrm2 = 0.0, nrmX = 0.0;

  memset (Ax, 0, m * sizeof (double));

  for (j = 0; j < n; j++)
    {

      nrmX += pow (x[j], 2);
      for (l = jc[j]; l < jc[j + 1]; l++)	// Ax += Ax + A(:, j) * x[j]
	Ax[ir[l]] += s[l] * x[j];
    }

  for (i = 0; i < m; i++)
    nrm2 += pow (Ax[i] - b[i] + z[i], 2);


  free (Ax);

  return sqrt (nrm2 / nrmX);

}


/* ------------------------------------------------------------------------------- */
/*	 Given a matrix A, x, b computes norm(A * x - b , 2)                       */
/* ------------------------------------------------------------------------------- */
double
residError (const MAT * A, double *x, const double *b, const double *z)
{

  int i;
  ptrdiff_t mBlas = A->m, nBlas = A->n, incx = 1, incy = 1;
  double dbl_one = 1, minus_one = -1;

  double *Ax = (double *) malloc (A->m * sizeof (double));
  memcpy (Ax, b, A->m * sizeof (double));	// Ax = b;


  for (i = 0; i < A->m; i++)
    Ax[i] -= z[i];

// Ax = (b - z);

  DGEMV ("N", &mBlas, &nBlas, &dbl_one, A->val, &mBlas, x, &incx, &minus_one,
	 Ax, &incy);

// Ax = A * x - b + z;

  free (Ax);

  return DNRM2 (&mBlas, Ax, &incx) / DNRM2 (&nBlas, x, &incx);

}

/* ------------------------------------------------------------------------------- */
/*	 Given a matrix A, compute the squared-norms of its columns                    */
/* ------------------------------------------------------------------------------- */
//
inline void
computeColNorms (const MAT * A, double *prob)
{

  size_t n = A->n, j;
  ptrdiff_t mBlas = A->m, incx = 1;

  memset (prob, 0, n * sizeof (double));
  for (j = 0; j < n; j++)
    {
      prob[j] = DNRM2 (&mBlas, (A->val + j * A->m), &incx);
      prob[j] = pow (prob[j], 2);
    }
};

/* ------------------------------------------------------------------------------- */
/*	 Given a matrix A, compute the squared-norms of its rows                   */
/* ------------------------------------------------------------------------------- */
inline void
computeRowNorms (const SMAT * A, double *prob)
{

  size_t m = A->m, n = A->n;
  size_t *ir = A->row_ptr, *jc = A->col_ind;
  double *s = A->sVal;

  int l, j, k;
  memset (prob, 0, m * sizeof (double));
  for (j = 0; j < n; j++)
    for (l = jc[j], k = jc[j + 1]; l < k; l++)
      prob[ir[l]] = prob[ir[l]] + pow (s[l], 2);
};


/* ------------------------------------------------------------------------------- */
/*	 Given a matrix A, compute the squared-norms of its columns                */
/* ------------------------------------------------------------------------------- */
inline void
computeColNormsSparse (const SMAT * A, double *prob)
{

  size_t n = A->n;
  size_t *jc = A->col_ind;
  double *s = A->sVal;

  int l, j, k;
  memset (prob, 0, n * sizeof (double));
  for (j = 0; j < n; j++)
    for (l = jc[j], k = jc[j + 1]; l < k; l++)
      prob[j] = prob[j] + pow (s[l], 2);
};
