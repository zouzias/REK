/*
 * types.h
 *
 *  Created on: 2012-12-21
 *      Author: zouzias
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>

/**
 * A two-dimensional dense matrix struct
 *
 * Elements are stored in a column-wise ordering in 1-dimensional array 
 */
struct matrix
{
  size_t m; /*!< Number of rows */
  size_t n; /*!< Number of columns */				
  double *val; /*!< Array of matrix entries */
};

typedef struct matrix MAT;


/**
 * A two-dimensional sparse matrix struct.
 *
 * It uses the compressed column sparse format (see netlib.org for details) 
 */
struct sparseMat
{
  size_t m;	/*!< Number of rows   */
  size_t n;	/*!< Number of columns */
  size_t *row_ptr, *col_ind; /*!< Row index and column pointer indices */
  double *sVal; /*!< Non-zero entries */
};

typedef struct sparseMat SMAT;


#endif /* TYPES_H_ */
