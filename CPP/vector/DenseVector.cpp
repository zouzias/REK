/*
 * DenseVector.cpp
 *
 *  Created on: May 3, 2015
 *      Author: zouzias
 */

#include "DenseVector.hpp"

void DenseVector::random(){
	for(int i = 0; i < vector_.size(); i++){
		vector_[i] = (double)rand() / RAND_MAX;
	}
};


int DenseVector::size() const{
	return vector_.size();
};

double DenseVector::get(int index) const{
	return vector_[index];
};


void DenseVector::set(int index, double value){
	vector_[index] = value;
};

void DenseVector::scale(double alpha){
	for(int i = 0; i < vector_.size(); i++){
		vector_[i] *= alpha;
	}
};


void DenseVector::minus(const DoubleVector& x){
	assert(vector_.size() == x.size());
	for(int i = 0; i < vector_.size(); i++){
		vector_[i] -= x.get(i);
	}
};

std::vector<double>& DenseVector::asList(){
	return vector_;
};
