/*
 * DoubleVector.cpp
 *
 *  Created on: May 3, 2015
 *      Author: zouzias
 */

#include "DoubleVector.hpp"

		DoubleVector::DoubleVector(){
			_size = DEFAULT_SIZE;
		};

		DoubleVector::DoubleVector(int size){
			_size = size;
		};

		double DoubleVector::DNRM2(){
			double nrm2 = 0.0;

			for(int i = 0; i < _size; i++){
				nrm2 += get(i) * get(i);
			}

			return nrm2;
		};

    void DoubleVector::DAXPY(double alpha, const DoubleVector& x){
			for(int i = 0; i < _size; i++){
				set(i, get(i) + alpha * x.get(i));
			}
    };

    double DoubleVector::DDOT(const DoubleVector& x){
			double value = 0.0;
			if ( _size != x.size())
				return 0.0;

			for( int i = 0 ; i < _size; i++){
				value += get(i) * x.get(i);
			}
    	return value;
    };

		void DoubleVector::minus(const DoubleVector& x){
			this->DAXPY(-1, x);
		};

		std::vector<double>* DoubleVector::asVector(){
			std::vector<double>* vec = new std::vector<double>(size());

			for ( int i = 0; i < vec->size(); i++){
				(*vec)[i] = get(i);
			}

			return vec;
		};
