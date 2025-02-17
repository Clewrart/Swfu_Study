package org.example;

public class Main {
    public static void main(String[] args) {
        int n = 10;
        int[] fib = Fibonacci.compute(n);

        if (fib != null) {
            for (int i : fib) {
                System.out.print(" " + i);
            }
        }
    }
}