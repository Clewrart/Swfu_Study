package org.example;

/**
 * 圆类
 */
public class Circle extends Shape {
    private double radius;  // 圆的半径

    /**
     * 构造函数
     * @param radius 圆的半径
     */
    public Circle(double radius) {
        this.radius = radius;
    }

    @Override
    public double area() {
        return Math.PI * radius * radius;
    }
}
