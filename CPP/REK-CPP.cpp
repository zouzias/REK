//============================================================================
// Name        : REK-CPP.cpp
// Author      : Anastasios Zouzias
// Version     :
// Copyright   : Apache 2.0 License
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>

#include "samplers/AliasSampler.hpp"
#include "algorithms/REKSolver.hpp"


#include "matrix/impl/DenseMatrix.hpp"
#include "vector/DenseVector.hpp"

using namespace std;

int main(void) {
	int n = 10;

	DoubleMatrix* A = new DenseMatrix(n,n);
	DoubleVector* xopt = new DenseVector(n);
	xopt->random();
	A->random();
	DoubleVector* b = A->times(*xopt);

	cout<< "xopt is " <<endl;
	for (int i = 0 ; i < xopt->size(); i++){
		cout<< xopt->get(i) <<endl;
	}

	cout<< "B is " <<endl;
	for (int i = 0 ; i < b->size(); i++){
		cout<< b->get(i) <<endl;
	}

	cout<< "A is " <<endl;
	for (int i = 0 ; i < A->getRowDimension(); i++){
		for (int j = 0 ; j < A->getColumnDimension(); j++){
		cout<< A->get(i,j)<< " , ";
		}
		cout<<endl;
	}

	REKSolver solver = REKSolver();

	long ITERS = 10000000;
	DoubleVector* x = solver.solve(*A, *b, ITERS);

	cout<<"(x, xopt)"<<endl;
	for (int j = 0 ; j < A->getColumnDimension(); j++){
		cout<< x->get(j) << " , " << xopt->get(j) <<endl;
	}

	x->minus(*xopt);
	cout<< "Error is " << x->DNRM2() << endl;


	return 0;
}
