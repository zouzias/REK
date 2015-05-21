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
	std::vector<double> test(n);

	test[0] = n;
	for(int i = 1; i <n ; i++){
		test[i] = 1;
	}

	AliasSampler alias(test);

	alias.initSampler();


	std::vector<uint>* samples = alias.sample(30);

	for(int i = 0 ; i < samples->size(); i++){
		cout<<"Sample " << samples->at(i) << endl;
	}

	DoubleMatrix* A = new DenseMatrix(10,10);
	DoubleVector* xopt = new DenseVector(10);
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

	cout<< "B is " <<endl;
	for (int i = 0 ; i < A->getRowDimension(); i++){
		for (int j = 0 ; j < A->getColumnDimension(); j++){
		cout<< A->get(i,j)<< " , ";
		}
		cout<<endl;
	}


	REKSolver solver = REKSolver();

	long ITERS = 1000;
	DoubleVector* x = solver.solve(*A, *b, ITERS);


	x->minus(*xopt);
	cout<< "Error is " << x->DNRM2();


	cout<<"Hello World" <<endl;
	return 0;
}
