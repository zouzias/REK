
#ifndef _REKutils_HPP
#define _REKutils_HPP

#include<stddef.h>		// for size_t

/* size_t is a type that represents size values, such as array dimensions. Use this function for cross-platform flexibility. By default, size_t is equivalent to int in C. When using the mex -largeArrayDims switch, size_t is equivalent to size_t in C. In Fortran, size_t is similarly equivalent to INTEGER*4 or INTEGER*8, based on platform and compilation flags. (from http://www.mathworks.com/help/matlab/apiref/size_t.html)
 */

double wtime ();

/**
 * Create matrix transpose of dense A
 *
 *
 * @param  A (Input) Matrix given in a "struct matrix". 
 * @return A transposed stored in "struct matrix"
 */
MAT *createTransp (const MAT * A);

/**
 * Store matrix in compressed row sparse format
 *
 * Input matrix A is stored in compressed column sparse format, output is stored in compressed row sparse format
 *
 * @param  A (Input) matrix stored in compressed colunm sparse format
 * @return Output matrix is stored in compressed row sparse format
 */
SMAT *createRowCompressed (const SMAT * A);

/**
 * Destructor for MAT struct
 *
 *
 * @param  A (Input) Matrix given in a "struct matrix". 
 * @return none
 */
void freeMAT (MAT * A);

/**
 * Destructor for SMAT struct
 *
 *
 * @param  A (Input) Sparse matrix in strcut sparseMat 
 * @return none
 */
void freeSMAT (SMAT * A);

/**
 * Compute the square column norms of input dense A. Output stored in prob.
 *
 *
 * @param  A (Input) Dense matrix stored as struct matrix
 * @param  prob (Output) Vector containing column norms squared  
 * @return none
 */
void computeColNorms (const MAT * A, double *prob);

/**
 * Computes norm( A * x - (b - z), 2)
 *
 *
 * @param  A (Input) Dense matrix stored in struct matrix 
 * @param  x (Input) Vector
 * @param  b (Input) Vector
 * @param  z (Input) Vector
 * @return The Euclidean norm of the vector A * x - (b - z)
 */
double residError (const MAT * A, double *x, const double *b,
		   const double *z);


/**
 * Compute the square row norms of input sparse A. Output stored in prob.
 *
 *
 * @param  A (Input) Sparse matrix stored as struct sparseMat
 * @param  prob (Output) Vector containing square row norms  
 * @return none
 */
void computeRowNorms (const SMAT * A, double *prob);

/**
 * Compute the square column norms of input sparse A. Output stored in prob.
 *
 *
 * @param  A (Input) Sparse matrix stored as struct sparseMat.
 * @param  prob (Output) Vector containing sparse column norms.  
 * @return none
 */
void computeColNormsSparse (const SMAT * A, double *prob);

/**
 * Computes norm( A * x - (b - z), 2)
 *
 *
 * @param  A (Input) Sparse matrix stored in struct sparseMat 
 * @param  x (Input) Vector
 * @param  b (Input) Vector
 * @param  z (Input) Vector
 * @return The Euclidean norm of the vector A * x - (b - z)
 */
double residErrorSparse (const SMAT * A, const double *x, const double *b,
			 const double *z);


#endif
