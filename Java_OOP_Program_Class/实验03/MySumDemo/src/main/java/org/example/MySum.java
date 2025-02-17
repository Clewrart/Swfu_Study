package org.example;

public class MySum {
    public static long sum() {
        int x = 1;

        int sum = 0;

        for (int i = 1; i <= 10; i++) {

            x = x * i;

            sum = sum + x;

        }
        return sum;
    }
}

