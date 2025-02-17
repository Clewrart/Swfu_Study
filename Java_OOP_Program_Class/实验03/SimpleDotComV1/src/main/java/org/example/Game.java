package org.example;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Game {
    public static void main(String[] args) {
        DotCom dotCom = new DotCom(5);
        boolean isAlive = true;
        Scanner scanner = new Scanner(System.in);
        int guess;
        EGameResult result;
        int guetime = 0;//猜测次数（不是猜对总次数）

        /*检查并处理重复猜测的情况 bool法
        boolean[] guessed = new boolean[7];
        Arrays.fill(guessed, false);*/

        //动态法
        ArrayList <Integer> guessed =
                new ArrayList <>();



        while (isAlive) {
            System.out.print("请输入一个整数：");
            guess = scanner.nextInt();
            guetime++;//获取输入1次就+1

            // 检查并处理重复猜测的情况bool法
            /*
            if (guessed[guess]) {
                System.out.println("无效猜测！这个数字已经猜过啦！！\n");
                System.out.print("当前猜测次数："+guetime);
                System.out.println("\n");
                continue;
            }
            guessed[guess] = true;
             */

            //动态法

            if (guessed.contains(guess))
            {
                System.out.println("无效猜测！这个数字已经猜过啦！！\n");

                System.out.print("当前猜测次数："+guetime);
                System.out.println("\n");
                continue;
            }
            guessed.add(guess);
            result = dotCom.checkUserGuess(guess);

            switch (result) {
                case MISS -> System.out.println("Miss");
                case HIT -> System.out.println("Hit");
                case DUNK -> {
                    System.out.println("Dunk");
                    isAlive = false;
                }
            }
            System.out.print("当前猜测次数："+guetime);
            System.out.println("\n");
        }

        System.out.print("总猜测次数："+guetime);
    }
}