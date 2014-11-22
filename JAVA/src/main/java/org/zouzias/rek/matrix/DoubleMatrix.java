package org.zouzias.matrix;

import org.zouzias.vector.DoubleVector;

/** Interface for a matrix with double entries.
 *
 */
public interface DoubleMatrix {

    /**
     * Fill in the entries with random values
     * 
     */
    public void random();

    /**
     * Get the number of rows
     * 
     * @return
     */
    public int getRowDimension();

    /**
     * Get the number of columns
     *
     * @return
     */
    public int getColumnDimension();

    /**
     * Get the i-th row
     * 
     * @param i
     * @return
     */
    public DoubleVector getRow(int i);

    /**
     * Get the j-th column
     *
     * @param j
     * @return
     */
    public DoubleVector getColumn(int j);

    /**
     * Compute a distribution over the rows. Namely, the i-th row A_i has probability mass
     *  ||A_i||_2^2 / ||A||_F^2 where ||A||_F^2 is the Frobenius norm of A 
     *
     * @return A vector of size equal to the number of rows containing the above probability distribution.
     */
    public DoubleVector rowNorms();

    /**
     * Compute a distribution over the columns. Namely, the j-th column A(j) has probability mass
     *  ||A(j)||_2^2 / ||A||_F^2 where ||A||_F^2 is the Frobenius norm of A 
     *
     * @return A vector of size equal to the number of column containing the above probability distribution.
     */
    public DoubleVector columnNorms();

    /**
     * Computes y = A * x
     *
     * @param x
     * @return y
     */
    public DoubleVector times(DoubleVector x); // y = A * x

    /** 
     * Frobenius norm of a matrix A, i.e., normF(A)= sqrt(sum_{i,j} A(i,j)^2)
     *
     * @return
     */
    public double normF(); // Frobenius norm of matrix

    /**
     * Get (i,j) entry of matrix
     *
     * @param i
     * @param j
     * @return
     */
    public double get(int i, int j);

    /**
     * Set (i,j)-th entry of matrix to s
     *
     * @param i
     * @param j
     * @param s
     */
    public void set(int i, int j, double s);
}
