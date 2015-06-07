/*
 * REKSolver.cpp
 *
 *  Created on: May 4, 2015
 *      Author: zouzias
 */

#include "REKSolver.hpp"

#include "../vector/DenseVector.hpp"
#include "../samplers/AliasSampler.hpp"
#include <stdlib.h>


DoubleVector*	 REKSolver::solve(const DoubleMatrix& A, const DoubleVector& b, double MaxSeconds){
	DoubleVector* vector = new DenseVector();

	return vector;
};


DoubleVector* REKSolver::solve(const DoubleMatrix& A, const DoubleVector& b, long MaxIterations){

	double val;
  int i_k, j_k;
  DoubleVector* x = new DenseVector(A.getColumnDimension());
  DoubleVector* z = new DenseVector(b);
  DoubleVector* rowNorms = A.rowNorms();
	DoubleVector* columnNorms = A.columnNorms();

  AliasSampler rowSampler(*rowNorms);
	AliasSampler colSampler(*columnNorms);

	// Initialize Alias samplers, O(n)
	rowSampler.initSampler();
	colSampler.initSampler();

  for (int k = 0; k < MaxIterations; k++) {
  	//i_k = rowSampler.walkerSample();
  	//j_k = colSampler.walkerSample();

		// Extended Kaczmarz
		i_k = k % A.getRowDimension();
		j_k = k % A.getColumnDimension();


    val = -z->DDOT(A.getColumn(j_k)) / columnNorms->get(j_k);     // val = - dot(z, A(:, j_k)) / colProbs(j_k)
    z->DAXPY(val, A.getColumn(j_k));                             // z = z + val * A(:, j_k);

    val = x->DDOT(A.getRow(i_k));                                // val = dot(x, A(i_k, :))
    val = (b.get(i_k) - z->get(i_k) - val) / rowNorms->get(i_k);  // val = (b(i_k) - z(i_k) - val) / roProbs(i_k)
    x->DAXPY(val, A.getRow(i_k));                                // x = x + val * A(i_k, :);
  }

	delete z;
	delete rowNorms;
	delete columnNorms;

  return x;
};
