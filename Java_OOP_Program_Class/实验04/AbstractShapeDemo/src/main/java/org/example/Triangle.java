package org.example;

/**
 * 三角形类
 */
public class Triangle extends Shape {
    private double lenx;
    private double leny;
    private double lenz;

    public Triangle(double lenx, double leny, double lenz) {
        this.lenx = lenx;
        this.leny = leny;
        this.lenz = lenz;
    }

    @Override
    public double area() {
        double s = (this.lenx+this.leny+this.lenz) / 2.0;
        return Math.sqrt(s*(s - lenx)*(s - leny)*(s - lenz));
    }
}

