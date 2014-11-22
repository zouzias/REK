package org.zouzias.matrix;

import java.util.ArrayList;
import java.util.List;
import org.zouzias.utils.NAUtils;
import org.zouzias.vector.DenseVector;
import org.zouzias.vector.DoubleVector;
import org.zouzias.vector.SparseVector;

/** A sparse matrix implementation. The current implementation stores the matrix 
 * as a list of sparse row vectors but also as a list of sparse column vector. 
 * 
 * There is a redundancy on the space requirements, however this provides efficient computation 
 * on the randomized Extended Kaczmarz method. It uses stores the matrix in terms of rows 
 * and columns. It requires twice the space needed for storing a matrix since each (i,j) entry can
 * be access via rows.get(i).get(j) and columns.get(j).get(i). 
 */
public class SparseMatrix implements DoubleMatrix {

    private List<SparseVector> rows = new ArrayList<SparseVector>();    // Stored By rows
   private List<SparseVector> columns = new ArrayList<SparseVector>();  // Stored by columns

    /**
     * Construct a new sparse matrix in CCS format.
     *
     * @param m 
     * @param n 
     */
    public SparseMatrix(int m, int n) {
        for (int i = 0; i < m; i++)
            rows.add(new SparseVector(n));

        for (int j = 0; j < n; j++)
            columns.add(new SparseVector(m));
    }

    /**
     * Converts a dense matrix to a sparse one (without affecting the dense one)
     *
     * @param A 
     */
    public SparseMatrix(double[][] A) {

        int m = A.length, n = A[0].length;

        for (int i = 0; i < m; i++)
            if (A[i].length != n)
                throw new IllegalArgumentException("All rows must have the same length.");

        for (int i = 0; i < m; i++)
            rows.add(new SparseVector(A[i]));

        for (int j = 0; j < n; j++)
            columns.add(new SparseVector(m));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) 
                columns.get(j).set(i, A[i][j]);
    }

    /**
     *
     * @param A
     * @param m
     * @param n
     */
    public SparseMatrix(double[][] A, int m, int n) {
        for (int i = 0; i < m; i++)
            rows.add(new SparseVector(A[i]));

        for (int j = 0; j < n; j++)
            columns.add(new SparseVector(m));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) 
                columns.get(j).set(i, A[i][j]);
    }

    @Override
    public void random() {
        for (int i = 0, m = rows.size(); i < m; i++)
            for (int j = 0, n = columns.size(); j < n; j++) {
                double val = Math.random();
                rows.get(i).set(j, val);
                columns.get(j).set(i, val);
            }
    }

    @Override
    public int getRowDimension() {
        return rows.size();
    }

    @Override
    public int getColumnDimension() {
        return columns.size();
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
        DoubleVector row = new DenseVector(rows.size());
        for (int i = 0, m = rows.size(); i < m; i++)
            row.set(i, Math.pow(getRow(i).DNRM2(), 2.0));

        return row;
    }

    @Override
    public DoubleVector columnNorms() {
        DoubleVector col = new DenseVector(columns.size());
        for (int j = 0, n = columns.size(); j < n; j++)
            col.set(j, Math.pow(getColumn(j).DNRM2(), 2.0));

        return col;
    }

    @Override
    public DoubleVector times(DoubleVector x) {
        int m = getRowDimension(), n = getColumnDimension();
        if (x.size() != n)
            throw new IllegalArgumentException("Matrix inner dimensions must agree.");

        DoubleVector y = new DenseVector(m);
        for (int j = 0; j < n; j++)
            y.DAXPY(x.get(j), getColumn(j));

        return y;
    }

    @Override
    public double normF() {
        double norm = 0;
        for (int i = 0; i < rows.size(); i++)
            norm = NAUtils.hypot(norm, rows.get(i).DNRM2());
       
        return norm;
    }

    @Override
    public void set(int i, int j, double s) {
        rows.get(i).set(j, s);
        columns.get(j).set(i, s);
    }

    @Override
    public double get(int i, int j) {
        return rows.get(i).get(j);
    }
}
