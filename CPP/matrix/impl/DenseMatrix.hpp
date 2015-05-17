/*
 * DenseMatrix.hpp
 *
 *  Created on: May 4, 2015
 *      Author: zouzias
 */

#ifndef DENSEMATRIX_HPP_
#define DENSEMATRIX_HPP_

#include "../DoubleMatrix.hpp"

class DenseMatrix : public DoubleMatrix {

public:

			DenseMatrix(){

			};

			~DenseMatrix(){

			};

			virtual void random(){

			};

	    virtual int getRowDimension()  const{

			}

			virtual int getColumnDimension()  const{

			}

			virtual DoubleVector& getRow(int i)  const{

			}

			virtual DoubleVector& getColumn(int j) const{

			}

			virtual DoubleVector& rowNorms()  const{

			}

			virtual DoubleVector& columnNorms()  const{

			}

			virtual DoubleVector& times(const DoubleVector& x) const{

			}

			virtual double normF() const{

			}

			virtual double get(int i, int j) const {

			}
};

#endif /* DENSEMATRIX_HPP_ */
