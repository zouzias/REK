/*
 * REKSolver.hpp
 *
 *  Created on: May 4, 2015
 *      Author: zouzias
 */

#ifndef REKSOLVER_HPP_
#define REKSOLVER_HPP_

#include "LeastSquaresSolver.hpp"

class REKSolver : public LeastSquaresSolver{

public:

	REKSolver(){

	}

	DoubleVector& solve(DoubleMatrix& A, DoubleVector& b, double MaxSeconds);
	DoubleVector& solve(DoubleMatrix& A, DoubleVector& b, long MaxIterations);
};


#endif /* REKSOLVER_HPP_ */
