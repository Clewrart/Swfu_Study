package org.example;

public class Main {
    public static void main(String[] args) {
        double[] es = {2.7, 3.2, 1.5};
        Triangle triangle = new Triangle(es[0], es[1], es[2]);
        double s = triangle.area();
        System.out.println("三角形的面积：" + s);
    }
}