/*
 * This file provides a mex implementation of the algorithm that is described in [1].
 *
 * References :
 * [1] - Randomized Extended Kaczmarz for Solving Least Squares
 *       Anastasios Zouzias and Nikolaos Freris
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

#include "REKBLAS_mex.h"
#include "REKBLAS.h"


void
mexFunction (int nargout, mxArray * pargout[], int nargin,
	     const mxArray * pargin[])
{
  /* Local variables used in REK */
  mwSize m, n, k, l;
  unsigned int i, iters;
  double *x, *b, dt;

  /* check: only one input and one output argument */
  if (nargin != 4)
    mexErrMsgTxt
      ("Must have three input arguments.\n Sample execution: [x, time] = REKblas_mex(A, b, MAXITERS, TOL);\n");
  if (nargout != 2)
    mexErrMsgTxt
      ("Must have one output argument.\n Sample execution: [x, time] = REKblash_mex(A, b, MAXITERS, TOL)\n");

  /* prevent you from passing a sparse matrix,
   * a string matrix, or a complex array. mxIsComplex
   * is used to determine if there is an imaginary
   * part of the mxArray. mxIsClass is used to determine
   * if the mxArray belongs to a particular class */

  if (mxIsComplex (pargin[0]) || mxIsChar (pargin[0]))
    mexErrMsgTxt ("Input must be real and nonstring");

  /* initialize random seed: */
  srand (time (NULL));

  // Get the dimensions of the input matrix A (m x n).
  m = mxGetM (pargin[0]);
  n = mxGetN (pargin[0]);

  // Get the dimensions of the input vector b
  k = mxGetM (pargin[1]);
  l = mxGetN (pargin[1]);

  iters = mxGetScalar (pargin[2]);	// Maximum number of iterations
  TOL = mxGetScalar (pargin[3]);	// Accuracy or tolerance of algorithm

  if (k != m || l > 1)
    mexErrMsgTxt
      ("Input must be an m x n matrix A, and an m dimensional vector b");

  /* Create an mxArray for the output data */
  pargout[0] = mxCreateDoubleMatrix (n, 1, mxREAL);
  x = mxGetPr (pargout[0]);

  BLOCKSIZE = 8 * MIN (m, n);

  b = (double *) mxMalloc (m * sizeof (double));

  //-----------------------------------------------------    
  // Densify right hand side "b" (if sparse)
  //-----------------------------------------------------
  if (mxIsSparse (pargin[1]))
    {
      /* Sparse matrix data structure in compressed column format */
      mwSize *irB = mxGetIr (pargin[1]);	/* Row indexing      */
      mwSize *jcB = mxGetJc (pargin[1]);	/* Column count      */
      double *sB = mxGetPr (pargin[1]);	/* Non-zero elements */

      memset (b, 0, m * sizeof (double));
      for (i = 0; i < jcB[1]; i++)
	b[irB[i]] = sB[i];
    }
  else
    {
      double *b_ptr = mxGetPr (pargin[1]);
      memcpy (b, b_ptr, m * sizeof (double));
    }
  //-----------------------------------------------------

  if (mxIsSparse (pargin[0]))
    {				// Input matrix is sparse (REK_sparse)

      /* Sparse matrix data structure in compressed column format */
      mwSize *ir = mxGetIr (pargin[0]);	/* Row indexing      */
      mwSize *jc = mxGetJc (pargin[0]);	/* Column count      */
      double *s = mxGetPr (pargin[0]);	/* Non-zero elements */

      size_t nnz = jc[n];

      SMAT *A = (SMAT *) malloc (sizeof (SMAT));
      A->m = m;
      A->n = n;
      A->row_ptr = (size_t *) malloc (nnz * sizeof (size_t));
      A->col_ind = (size_t *) malloc ((n + 1) * sizeof (size_t));
      A->sVal = (double *) malloc (nnz * sizeof (double));

      memcpy (A->row_ptr, ir, nnz * sizeof (mwSize));
      memcpy (A->col_ind, jc, (n + 1) * sizeof (mwSize));
      memcpy (A->sVal, s, nnz * sizeof (double));

      dt = -wtime ();
      REKBLAS_Sparse (x, A, b, iters);
      dt += wtime ();

      freeSMAT (A);

    }
  else
    {				// Input matrix is dense

      MAT *A = malloc (sizeof (MAT));
      A->m = m;
      A->n = n;
      A->val = (double *) malloc (m * n * sizeof (double));

      double *Aptr = mxGetPr (pargin[0]);
      memcpy (A->val, Aptr, m * n * sizeof (double));

      dt = -wtime ();
      REKBLAS_Dense (x, A, b, iters);
      dt += wtime ();

      freeMAT (A);
    }

  printf("REK-BLAS elapsed time: %.4f\n", dt);

  // Keep track of running time
  pargout[1] = mxCreateDoubleScalar (dt);

  mxFree (b);

};				// End of mex main function
