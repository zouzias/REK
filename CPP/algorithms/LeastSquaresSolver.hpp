/*
 * LeastSqyaresSolver.hpp
 *
 *  Created on: May 4, 2015
 *      Author: zouzias
 */

#ifndef LEASTSQUARESSOLVER_HPP_
#define LEASTSQUARESSOLVER_HPP_

#include "../vector/DoubleVector.hpp"
#include "../matrix/DoubleMatrix.hpp"

class LeastSquaresSolver{

public:
	 /** The solver will only run for MaxSeconds seconds and then will terminate
	     *
	     * @param A
	     * @param b
	     * @param MaxSeconds
	     * @return
	     */
	    virtual DoubleVector& solve(DoubleMatrix& A, DoubleVector& b, double MaxSeconds) = 0;

	    /** The solver will perform only MaxIterations iterations
	     *
	     * @param A A real matrix A
	     * @param b A
	     * @param MaxIterations
	     * @return
	     */
	    virtual DoubleVector& solve(DoubleMatrix& A, DoubleVector& b, long MaxIterations) = 0;
};


#endif /* LEASTSQYARESSOLVER_HPP_ */
