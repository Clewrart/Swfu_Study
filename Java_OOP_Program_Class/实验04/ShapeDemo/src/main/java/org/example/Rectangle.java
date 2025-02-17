package org.example;

/**
 * 矩形类
 */
public class Rectangle extends Shape {
    private double height;  // 高度
    private double width;  // 宽度

    /**
     * 构造函数
     * @param height 高度
     * @param width 宽度
     */
    public Rectangle(double height, double width) {
        this.height = height;
        this.width = width;
        System.out.println("Rectangle::Rectangle()");
    }
}
