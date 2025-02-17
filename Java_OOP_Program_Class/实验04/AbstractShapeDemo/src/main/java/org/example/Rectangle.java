package org.example;

/**
 * 矩形类
 */
public class Rectangle extends Shape {

    private double width;
    private double length;

    public Rectangle(double width, double length) {
        this.width = width;
        this.length = length;
    }
    @Override
    public double area() {
        return width*length;
    }
}
