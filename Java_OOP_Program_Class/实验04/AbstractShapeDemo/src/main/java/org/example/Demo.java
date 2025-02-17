package org.example;

public class Demo {
    public static void main(String[] args) {
        Shape s1 = new Circle(2.0);
        Shape s2 = new Triangle(3.0,4.0,5.0);
        Shape s3 = new Rectangle(2.0,3.6);

        Shape[] shapes = new Shape[3];
        shapes[0] = s1;
        shapes[1] = s2;
        shapes[2] = s3;

        for (Shape s : shapes) {
            System.out.printf("该形状的面积是：%f%n", s.area());
        }
    }
}