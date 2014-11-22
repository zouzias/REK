package org.zouzias.matrix;

import java.util.ArrayList;
import java.util.List;
import org.zouzias.utils.NAUtils;
import org.zouzias.vector.DenseVector;
import org.zouzias.vector.DoubleVector;

/**
 * An implementation of a dense real matrix. 
 * 
 * There is a redundancy on the space requirements, however this provides efficient computation 
 * on the randomized Extended Kaczmarz method. The current class stores the matrix in terms of rows 
 * and columns. It requires twice the space needed for storing a matrix since each (i,j) entry can
 * be access via rows.get(i).get(j) and columns.get(j).get(i). 
 *
 */
public final class DenseMatrix implements DoubleMatrix {
    /**
     * Array for internal storage of elements.
     *
     * @serial internal array storage.
     */
    private List<DoubleVector> rows; // Stored By rows
    private List<DoubleVector> columns; // Stored by columns
    /**
     * Row and column dimensions.
     *
     * @serial row dimension.
     * @serial column dimension.
     */
    private int m, n;

    /**
     * Construct an m-by-n matrix of zeros.
     *
     * @param m Number of rows.
     * @param n Number of colums.
     */
    public DenseMatrix(int m, int n) {
        this.m = m;
        this.n = n;
        rows = new ArrayList<DoubleVector>();
        columns = new ArrayList<DoubleVector>();

        for (int i = 0; i < m; i++)
            rows.add(new DenseVector(n));

        for (int j = 0; j < n; j++)
            columns.add(new DenseVector(m));

    }

    /**
     * Construct a matrix from a 2-D array.
     *
     * @param A Two-dimensional array of doubles.
     * @exception IllegalArgumentException All rows must have the same length
     * @see #constructWithCopy
     */
    public DenseMatrix(double[][] A) {
        m = A.length;
        n = A[0].length;
        for (int i = 0; i < m; i++)
            if (A[i].length != n)
                throw new IllegalArgumentException("All rows must have the same length.");

        rows = new ArrayList<DoubleVector>();
        columns = new ArrayList<DoubleVector>();

        for (int i = 0; i < m; i++)
            rows.add(new DenseVector(A[i]));

        for (int j = 0; j < n; j++)
            columns.add(new DenseVector(m));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) 
                columns.get(j).set(i, A[i][j]);
    }

    /**
     * Construct a matrix quickly without checking arguments.
     *
     * @param A Two-dimensional array of doubles.
     * @param m Number of rows.
     * @param n Number of columns.
     */
    public DenseMatrix(double[][] A, int m, int n) {
        this.m = m;
        this.n = n;

        rows = new ArrayList<DoubleVector>();
        columns = new ArrayList<DoubleVector>();

        for (int i = 0; i < m; i++)
            rows.add(new DenseVector(A[i]));

        for (int j = 0; j < n; j++)
            columns.add(new DenseVector(m));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) 
                columns.get(j).set(i, A[i][j]);
    }

    /**
     * Get row dimension.
     *
     * @return m, the number of rows.
     */
    @Override
    public int getRowDimension() {
        return m;
    }

    /**
     * Get column dimension.
     *
     * @return n, the number of columns.
     */
    @Override
    public int getColumnDimension() {
        return n;
    }

    /**
     * Get a single element.
     *
     * @param i Row index.
     * @param j Column index.
     * @return A(i,j)
     * @exception ArrayIndexOutOfBoundsException
     */
    @Override
    public double get(int i, int j) {
        return rows.get(i).get(j);
    }

    /**
     * Set a single element.
     *
     * @param i Row index.
     * @param j Column index.
     * @param s A(i,j).
     * @exception ArrayIndexOutOfBoundsException
     */
    @Override
    public void set(int i, int j, double s) {
        rows.get(i).set(j, s);
        columns.get(j).set(i, s);
    }

    @Override
    public double normF() {
        double norm = 0;
        for (int i = 0; i < rows.size(); i++)
            norm = NAUtils.hypot(norm, rows.get(i).DNRM2());
       
        return norm;
    }

    @Override
    public DoubleVector times(DoubleVector x) {
        if (n != x.size())
            throw new IllegalArgumentException("Matrix inner dimensions must agree.");

        DoubleVector y = new DenseVector(m);

        for (int j = 0; j < n; j++)
            y.DAXPY(x.get(j), this.getColumn(j));

        return y;
    }

    @Override
    public void random() {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                double val = Math.random();
                rows.get(i).set(j, val);
                columns.get(j).set(i, val);
            }
    }

    @Override
    public DoubleVector getRow(int i) {
        return rows.get(i);
    }

    @Override
    public DoubleVector getColumn(int j) {
        return columns.get(j);
    }

    @Override
    public DoubleVector rowNorms() {
        DoubleVector row = new DenseVector(m);
        for (int i = 0; i < m; i++)
            row.set(i, Math.pow(getRow(i).DNRM2(), 2.0));

        return row;
    }

    @Override
    public DoubleVector columnNorms() {
        DoubleVector col = new DenseVector(n);
        for (int j = 0; j < n; j++)
            col.set(j, Math.pow(getColumn(j).DNRM2(), 2.0));

        return col;
    }
}
