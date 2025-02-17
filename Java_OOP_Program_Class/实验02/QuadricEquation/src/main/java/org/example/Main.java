package org.example;

public class Main {
    public static void main(String[] args) {
        double a = 1.0;
        double b = 2.5;
        double c = 0.5;

        // 创建一元二次方程类的对象实例
        QuadricEquation qe = new QuadricEquation(a, b, c);
        // 计算一元二次方程的实根
        double[] xs = qe.findRoot();

        if (xs == null) {
            System.out.println("该一元二次方程没有实根。");
        } else if (xs.length == 1) {
            System.out.print("该一元二次方程有一个实根：");
            for (double x : xs) {
                System.out.print(" " + x);
            }
        } else {
            System.out.println("该一元二次方程有两个实根");
            for (double x : xs) {
                System.out.println(" " + x);
            }
        }
    }
}