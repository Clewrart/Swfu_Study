package org.example;

/**
 * 三角形类
 */
public class Triangle {
    private double e1;
    private double e2;
    private double e3;

    /**
     * 计算三角形的面积
     * @return 返回三角形的面积
     */
    public Triangle (double x1,double x2,double x3){
        this.e1 = x1;
        this.e2 = x2;
        this.e3 = x3;
    }

    public double area() {
        double s = (this.e1+this.e2+this.e3) / 2.0;
        return Math.sqrt(s*(s - e1)*(s - e2 )*(s - e3));
    }
}
