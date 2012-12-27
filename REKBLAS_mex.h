#ifndef _REKBLAS_MEX_HPP
#define _REKBLAS_MEX_HPP

#include <math.h>
#include <string.h>
#include "mex.h"
#include <time.h>
#include "types.h"

// Needed declarations for mex files.
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#include "matrix.h"
#define EXIT_ERROR mexErrMsgTxt ("failure") ;
#define EXIT_OK
#else
#define EXIT_ERROR exit (EXIT_FAILURE) ;
#define EXIT_OK exit (EXIT_SUCCESS) ;
#endif


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#endif
