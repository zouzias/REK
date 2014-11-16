#include "REKBLAS.h"

/*!< REK periodically checks for convergence after BLOCKSIZE iterations */
unsigned int BLOCKSIZE = 100;

/*!< Maximum number of iterations */
unsigned int MAXITERS = 10e4;


void
REKBLAS_Dense (MAT * A, double *x, const double *b, double TOL)
{

    int m = A->m, n = A->n, k, i_k, j_k;
    double val, val2, *z, *rowProb, *colProb;
    unsigned int *rowSampl, *colSampl;

    z = (double *) malloc (m * sizeof (double));
    rowProb = (double *) malloc (m * sizeof (double));
    colProb = (double *) malloc (n * sizeof (double));
    rowSampl = (unsigned int *) malloc (BLOCKSIZE * sizeof (unsigned int));
    colSampl = (unsigned int *) malloc (BLOCKSIZE * sizeof (unsigned int));

    // Copy A to A_transpose
    MAT *Atransp = createTransp (A);

    // Compute the sampling probabilities and the samples
    computeColNorms (A, colProb);	// Compute the column probabilities
    computeColNorms (Atransp, rowProb);	// Compute the columns probabilities of Atransp (n x m matrix)

    // Init alias sampler
    ALIAS *asRow = createAliasSampler (rowProb, m);
    ALIAS *asCol = createAliasSampler (colProb, n);

    // Sample indices
    mySampler (rowSampl, BLOCKSIZE, asRow);
    mySampler (colSampl, BLOCKSIZE, asCol);

    memcpy (z, b, m * sizeof (double));	// Initialize z: z = y;

    for (k = 0; k < MAXITERS; k++)
    {

        if ((k + 1) % BLOCKSIZE == 0 && residError (A, x, b, z) < TOL && residError(Atransp, z, b, b) < TOL)
        {
            printf ("-->REK_Dense stopped at %d <--\n", (int)k);
            break;
        }
        else if ((k + 1) % BLOCKSIZE == 0)
        {
            // Sample indices
            mySampler (rowSampl, BLOCKSIZE, asRow);
            mySampler (colSampl, BLOCKSIZE, asCol);
        }

        i_k = rowSampl[k % BLOCKSIZE];
        j_k = colSampl[k % BLOCKSIZE];

        val = DDOT ((int) m, z, 1, &(A->val)[j_k * m], 1);
        val /= colProb[j_k];

        val = -val;
        DAXPY ((int) m, val, &(A->val)[j_k * m], 1, z, 1);

        val2 =
        DDOT ((int) n, x, 1, &(Atransp->val)[i_k * n], 1);

        val2 = b[i_k] - z[i_k] - val2;
        val2 /= rowProb[i_k];

        DAXPY ((int) n, val2, &(Atransp->val)[i_k * n], 1, x, 1);
    }

    freeSampler (asRow);
    freeSampler (asCol);
    freeMAT (Atransp);

    free (z);
    free (rowProb);
    free (colProb);
    free (rowSampl);
    free (colSampl);
};

void
REKBLAS_Sparse (const SMAT * A, double *x, const double *b,
                double TOL)
{

    unsigned int k, l, i_k, j_k, *rowSampl, *colSampl;
    double val, *z, *rowProb, *colProb, *s = A->sVal;
    int m = A->m, n = A->n, *ir = A->row_ptr, *jc = A->col_ind;

    SMAT *Atransp = createRowCompressed (A);

    z = (double *) malloc (m * sizeof (double));
    rowProb = (double *) malloc (m * sizeof (double));
    colProb = (double *) malloc (n * sizeof (double));
    rowSampl = (unsigned int *) malloc (BLOCKSIZE * sizeof (unsigned int));
    colSampl = (unsigned int *) malloc (BLOCKSIZE * sizeof (unsigned int));

    // Compute the sampling probabilities and the samples
    computeRowNorms (A, rowProb);	// Compute the row probabilities
    computeColNormsSparse (A, colProb);	// Compute the column probabilities

    // Init alias sampler
    ALIAS *asRow = createAliasSampler (rowProb, m);
    ALIAS *asCol = createAliasSampler (colProb, n);

    // Sample indices
    mySampler (rowSampl, BLOCKSIZE, asRow);
    mySampler (colSampl, BLOCKSIZE, asCol);

    memcpy (z, b, m * sizeof (double));	// Initialize z: z = y;


    for (k = 0; k < MAXITERS; k++)
    {				// Perform the iterations

        if ((k + 1) % BLOCKSIZE == 0 && residErrorSparse (A, x, b, z) < TOL)
        {
            printf ("-->REK_Sparse stopped at %d <--\n", k);
            break;
        }
        else if ((k + 1) % BLOCKSIZE == 0)
        {
            // Sample indices
            mySampler (rowSampl, BLOCKSIZE, asRow);
            mySampler (colSampl, BLOCKSIZE, asCol);
        }

        i_k = rowSampl[k % BLOCKSIZE];
        j_k = colSampl[k % BLOCKSIZE];

        val = 0;
        for (l = jc[j_k]; l < jc[j_k + 1]; l++){	// val_* = <z, A(:, j_k)>
            val += z[ir[l]] * s[l];
        }

        val /= colProb[j_k];


        for (l = jc[j_k]; l < jc[j_k + 1]; l++)	// z = z - val * A(:, j_k);
            z[ir[l]] = z[ir[l]] - val * s[l];

        val = 0;

        for (l = Atransp->row_ptr[i_k]; l < Atransp->row_ptr[i_k + 1]; l++){
            val += x[Atransp->col_ind[l]] * Atransp->sVal[l];
        }

        val = b[i_k] - z[i_k] - val;
        val /= rowProb[i_k];

        for (l = Atransp->row_ptr[i_k]; l < Atransp->row_ptr[i_k + 1]; l++){
            x[Atransp->col_ind[l]] += val * Atransp->sVal[l];
        }
    }

    freeSampler (asRow);
    freeSampler (asCol);
    freeSMAT (Atransp);

    free (z);
    free (rowProb);
    free (colProb);
    free (rowSampl);
    free (colSampl);
};				// End of REK_Sparse
