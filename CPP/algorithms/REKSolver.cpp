/*
 * REKSolver.cpp
 *
 *  Created on: May 4, 2015
 *      Author: zouzias
 */

#include "REKSolver.hpp"

#include "../vector/DenseVector.hpp"


DoubleVector&	 REKSolver::solve(DoubleMatrix& A, DoubleVector& b, double MaxSeconds){
	DoubleVector* vector = new DenseVector();
	return *vector;
};


DoubleVector& REKSolver::solve(DoubleMatrix& A, DoubleVector& b, long MaxIterations){
	DoubleVector* vector = new DenseVector();
	return *vector;
};
