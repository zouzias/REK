/*
 * SparseMatrix.hpp
 *
 *  Created on: May 4, 2015
 *      Author: zouzias
 */

#ifndef SPARSEMATRIX_HPP_
#define SPARSEMATRIX_HPP_

#include "../DoubleMatrix.hpp"

class SparseMatrix : public DoubleMatrix{

public:

	SparseMatrix(){

	};

	~SparseMatrix(){

	};

	virtual void random(){

	}

	virtual int getRowDimension() const{

	}

	virtual int getColumnDimension() const{

	}

	virtual DoubleVector& getRow(int i) const{

	}

	virtual DoubleVector& getColumn(int j) const{

	}

	virtual DoubleVector& rowNorms() const{

	}

	virtual DoubleVector& columnNorms() const{

	}

	virtual DoubleVector& times(const DoubleVector& x) const{

	}

	virtual double normF() const{

	}

	virtual double get(int i, int j) const{

	}

	virtual void set(int i, int j, double s){

	}

};

#endif /* SPARSEMATRIX_HPP_ */
