/*
 * DenseVector.cpp
 *
 *  Created on: May 3, 2015
 *      Author: zouzias
 */

#include "DenseVector.hpp"

void DenseVector::random(){
	/* initialize random seed: */
	srand (time(NULL));

	for(int i = 0; i < _vector.size(); i++){
		_vector[i] = (double)rand() / RAND_MAX;
	}
};

int DenseVector::size() const{
	return _vector.size();
};

double DenseVector::get(int index) const{
	return _vector[index];
};

void DenseVector::set(int index, double value){
	_vector[index] = value;
};

void DenseVector::scale(double alpha){
	for(int i = 0; i < _vector.size(); i++){
		_vector[i] *= alpha;
	}
};

void DenseVector::minus(const DoubleVector& x){
	assert(_vector.size() == x.size());
	for(int i = 0; i < _vector.size(); i++){
		_vector[i] -= x.get(i);
	}
};
