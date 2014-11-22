package org.zouzias.utils;

/**
 * Numerical analysis tricks (for computing norms)
 *
 */
public class NAUtils {
    
     /** Compute the sqrt(a^2 + b^2)
     *
     * @param a
     * @param b
     * @return
     */
    public static double hypot(double a, double b) {
        double r;
        if (Math.abs(a) > Math.abs(b)) {
            r = b / a;
            r = Math.abs(a) * Math.sqrt(1 + r * r);
        } else if (b != 0) {
            r = a / b;
            r = Math.abs(b) * Math.sqrt(1 + r * r);
        } else
            r = 0.0;

        return r;
    }
    
}
