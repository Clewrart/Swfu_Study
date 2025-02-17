package org.example;

public class Main {
    public static void main(String[] args) {
        int[] years = { 1800, 2000, 2010, 2016, 2018, 2020 };

        for (int year : years) {
            if (LeapYear.isLeapYear(year)) {
                System.out.printf("Year %d is a leap year.\n", year);
            } else {
                System.out.printf("Year %d is not a leap year.\n", year);
            }
        }
    }
}