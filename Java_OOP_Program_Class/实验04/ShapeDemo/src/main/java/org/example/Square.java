package org.example;

/**
 * 正方形类
 */
public class Square extends Rectangle {
    public Square(double width) {
        super(width, width);
        System.out.println("Square::Square()");
    }
}
