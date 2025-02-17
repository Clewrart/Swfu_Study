package org.example;

import java.util.Random;
import java.util.Scanner;
import  java.util.random.*;


public class Game {
    public static void main(String[] args) {

        while (true) {
            boolean exit = false;
            final int guess;  // 保存用户输入
            String s;
            Card firstCard = new Card();
            Card secondCard = new Card();

            firstCard = Card.generate();
            secondCard = Card.generate();


            final Scanner scanner = new Scanner(System.in);
            System.out.print("哪一张扑克牌牌面更大？\n（输入'0'表示两张扑克牌相等，输入'1'表示第一张扑克牌更大，输入'2'表示第二张扑克牌更大）：");
            guess = scanner.nextInt();

            final int compareResult = firstCard.compareTo(secondCard);


            if ((guess == 0 && compareResult == 0) || (guess == 1 && compareResult > 0) || (guess == 2 && compareResult < 0)) {
                System.out.println("恭喜你，猜对了！");
            } else {
                System.out.println("很可惜，你猜错了！");
            }

            System.out.print("\n你想继续玩游戏吗？请输入 y 继续，n 结束：");
            String playAgain = scanner.next().toLowerCase();

            if ("n".equals(playAgain)) {
                exit = true; // 结束游戏
                break;
            }
        }
    }
}