package org.example;

/**
 * 一元二次方程类
 */
public class QuadricEquation {
    // 一元二次方程的三个系数
    private double a;
    private double b;
    private double c;

    /**
     * 一元二次方程类的构造函数
     * @param a
     * @param b
     * @param c
     */
    public QuadricEquation(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    /**
     * 计算一元二次方程的实根。
     * 如果一元二次方程有两个不同的实根，将两个不同的实根存储在一维数组root中；
     * 如果一元二次方程有两个相同的实根，将一个实根存储在一维数组root中；
     * 如果一元二次方程没有实根，则返回null。
     * @return 一元二次方程的实根。
     */

        public double[] findRoot() {
            double tmproot = b * b - 4 * a * c;//临时根


            if (tmproot > 0) {
                // 有两个不同
                 double root0 = (-b + Math.sqrt(tmproot)) / (2 * a);
                 double root1 = (-b - Math.sqrt(tmproot)) / (2 * a);
                 double root[] = {root0, root1};
                 return root;
            }

            else if (tmproot == 0) {
                // 有两个相同
                double root2 = -b / (2 * a);
                double root[]={root2};
                return root;
            }

            else {
                // 没有
                return null;
            }

        }
}