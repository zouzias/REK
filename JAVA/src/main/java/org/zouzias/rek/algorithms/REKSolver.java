package org.zouzias.algorithms;

import org.zouzias.matrix.DoubleMatrix;
import org.zouzias.samplers.AliasMethod;
import org.zouzias.vector.DenseVector;
import org.zouzias.vector.DoubleVector;

/**
 * Implementation of the randomized extended Kaczmarz method as in [1]. Alias method is used for 
 * non-uniform sampling (see AliasMethod class).
 *
 */
public class REKSolver implements LeastSquaresSolver {
    
    /**
     *
     */
    private static int CheckEvery = 1000;

    /** Executes the randomized extended Kaczmarz algorithm for maxSeconds seconds.
     *
     * @param A
     * @param b
     * @param maxSeconds
     * @return
     */
    @Override
    public DoubleVector solve(DoubleMatrix A, DoubleVector b, double maxSeconds) {

        long initTime = System.currentTimeMillis();
        double val;
        int i_k, j_k, k = 0;
        DoubleVector x = new DenseVector(A.getColumnDimension());
        DoubleVector z = new DenseVector(b);
        DoubleVector rowNorms = A.rowNorms(), colNorms = A.columnNorms();
        AliasMethod rowSampler = new AliasMethod(rowNorms.asList());
        AliasMethod colSampler = new AliasMethod(colNorms.asList());

        while ( k % CheckEvery != 0 || !timeIsUp(initTime, maxSeconds) ) {
            i_k = rowSampler.next();
            j_k = colSampler.next();

            val = -z.DDOT(A.getColumn(j_k)) / colNorms.get(j_k);        // val = - dot(z, A(:, j_k)) / colProbs(j_k) 
            z.DAXPY(val, A.getColumn(j_k));                             // z = z + val * A(:, j_k);

            val = x.DDOT(A.getRow(i_k));                                // val = dot(x, A(i_k, :))
            val = (b.get(i_k) - z.get(i_k) - val) / rowNorms.get(i_k);  // val = (b(i_k) - z(i_k) - val) / roProbs(i_k)
            x.DAXPY(val, A.getRow(i_k));                                // x = x + val * A(i_k, :);            
            
            k++;
        }

        return x;
    }

    /** Executes the randomized extended Kaczmarz algorithm for @MaxIterations iterations
     *
     * @param A
     * @param b
     * @param MaxIterations
     * @return
     */
    @Override
    public DoubleVector solve(DoubleMatrix A, DoubleVector b, long MaxIterations) {

        double val;
        int i_k, j_k;
        DoubleVector x = new DenseVector(A.getColumnDimension());
        DoubleVector z = new DenseVector(b);
        DoubleVector rowNorms = A.rowNorms(), columnNorms = A.columnNorms();

        AliasMethod rowSampler = new AliasMethod(rowNorms.asList());
        AliasMethod colSampler = new AliasMethod(columnNorms.asList());

        for (int k = 0; k < MaxIterations; k++) {
            i_k = rowSampler.next();
            j_k = colSampler.next();

            val = -z.DDOT(A.getColumn(j_k)) / columnNorms.get(j_k);     // val = - dot(z, A(:, j_k)) / colProbs(j_k) 
            z.DAXPY(val, A.getColumn(j_k));                             // z = z + val * A(:, j_k);

            val = x.DDOT(A.getRow(i_k));                                // val = dot(x, A(i_k, :))
            val = (b.get(i_k) - z.get(i_k) - val) / rowNorms.get(i_k);  // val = (b(i_k) - z(i_k) - val) / roProbs(i_k)
            x.DAXPY(val, A.getRow(i_k));                                // x = x + val * A(i_k, :);  
        }

        return x;
    }

    /** Check if the elapsed time is more than maxSeconds (with reference time referenceTime)
     */
    public boolean timeIsUp(double referenceTime, double maxSeconds) {
        return System.currentTimeMillis() - referenceTime > maxSeconds * 1000;
    }
}
