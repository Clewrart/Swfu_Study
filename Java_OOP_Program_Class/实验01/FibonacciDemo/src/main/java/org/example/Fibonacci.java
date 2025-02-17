package org.example;

/**
 * 斐波那契数列类
 */
public class Fibonacci {

    /**
     * 计算斐波那契数列的前n项
     * @param n 斐波那契数列的项数
     * @return 包含斐波那契数列前n项的一维数组
     */
    public static int[] compute(int n) {

        //存结果
        int[] fbResult = new int[n];

        //n等于1，结果0
        if (n == 1) {
            fbResult[0] = 0;

        } else if (n >= 2) {
            fbResult[0] = 0;
            fbResult[1] = 1;

            for (int i = 2; i < n; i++) {
                fbResult[i] = fbResult[i - 1] + fbResult[i - 2];
            }
        }

        return fbResult;
    }
}