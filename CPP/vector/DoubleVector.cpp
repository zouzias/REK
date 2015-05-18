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

    /**
     * DAXPY operation y <- y + alpha * x
     *
     * @param alpha
     * @param x
     */
    void DoubleVector::DAXPY(double alpha, const DoubleVector& x){
			for(int i = 0; i < _size; i++){
				set(i, get(i) + alpha * x.get(i));
			}
    };

    /**
     * Dot product with vector x
     *
     * @param x
     * @return
     */
    double DoubleVector::DDOT(const DoubleVector& x){
			double value = 0.0;
			if ( _size != x.size())
				return 0.0;

			for( int i = 0 ; i < _size; i++){
				value += get(i) * x.get(i);
			}
    	return value;
    };
