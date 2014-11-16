#include "aliasSampler.h"

ALIAS *
createAliasSampler(const double *prob, uint n) {

    uint j;
    double sum = 0;

    ALIAS *as = (ALIAS *) malloc(sizeof (ALIAS));
    as->n = n;
    as->A = (uint *) malloc((n + 2) * sizeof (uint));
    as->B = (uint *) malloc((n + 2) * sizeof (uint));
    as->Y = (double *) malloc((n + 2) * sizeof (double));

    for (j = 0; j < n; j++)
        sum += prob[j];
    sum = 1 / sum;

    // Normalize it now
    for (j = 0; j < n; j++)
        as->Y[j + 1] = prob[j] * sum;

    // Preprocess the sampler
    BuildSampler(as->Y, as->n, as->A, as->B);

    return as;
}

void
freeSampler(ALIAS * as) {
    free(as->A);
    free(as->B);
    free(as->Y);
    free(as);
}

inline void
mySampler(unsigned int *rb, uint iters, const ALIAS * as) {
    uint k;
    // Sample from Alias Sampler
    for (k = 0; k < iters; k++)
        rb[k] = WalkerSample(as->Y, as->n, as->A);
};


/*********************************************************************
 * Implementation of algorithm for sampling from a discrete
 * probability N-vector X[1], X[2], ..., X[N].  (N>=1.)
 * Runs on O(1) worst case time per sample,
 * and uses one integer and one real N-element array for storage.
 * Preprocessing consumes O(N) time and temporarily uses one
 * additional integer array (B[0..N+1]) for bookkeeping.
 * X[0] and X[N+1] are also used as sentinels in the Build() algorithm.
 *
 *  compile with    gcc -O9 -lm -lc  WDSsampler.c -o WDSsampler
 ****************Warren D. Smith August 2000**************************/

/* returns random sample i=1..N with prob X[i] */
uint
WalkerSample(const double *Y, uint N, const uint * A) {
    uint i;
    real r;
    /* Let i = random uniform integer from {1,2,...N};  */
    i = 1 + (uint) (N * drand48());
    r = drand48();
    if (r > Y[i])
        i = A[i];

    return i - 1;
}

/*overwrites X[1..N] by Y[1..N], creates A[1..N]. B[1..N] used for bookkeeping: */
void
BuildSampler(double *X, uint N, uint * A, uint * B) {
    uint i, j, k;
    assert(1 <= N);
    for (i = 1; i <= N; i++) {
        A[i] = i;
        B[i] = i; /* initial destins=stay there */
        assert(X[i] >= 0.0);
        X[i] = X[i] * N; /* scale probvec */
    }
    B[0] = 0;
    X[0] = 0.0;
    B[N + 1] = N + 1;
    X[N + 1] = 2.0; /* sentinels */
    i = 0;
    j = N + 1;
    for (;;) {
        do {
            i++;
        } while (X[B[i]] < 1.0); /* find i so X[B[i]] needs more */
        do {
            j--;
        } while (X[B[j]] >= 1.0); /* find j so X[B[j]] wants less */
        if (i >= j)
            break;
        k = B[i];
        B[i] = B[j];
        B[j] = k; /* swap B[i], B[j] */
    }

    i = j;
    j++;
    while (i > 0) {
        while (X[B[j]] <= 1.0)
            j++;
        /* find j so X[B[j]] needs more */
        assert(X[B[i]] < 1.0); /* meanwhile X[B[i]] wants less */
        if (j > N)
            break;
        assert(j <= N);
        assert(X[B[j]] > 1.0);
        X[B[j]] -= 1.0 - X[B[i]]; /* B[i] will donate to B[j] to fix up */
        A[B[i]] = B[j];
        if (X[B[j]] < 1.0) { /* X[B[j]] now wants less so readjust ordering */
            assert(i < j);
            k = B[i];
            B[i] = B[j];
            B[j] = k; /* swap B[j], B[i] */
            j++;
        } else
            i--;
    }
}

/**********************************************************************/

