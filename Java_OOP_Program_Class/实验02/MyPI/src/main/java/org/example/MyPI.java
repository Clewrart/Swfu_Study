package org.example;

public class MyPI {
    /**
     * 通过级数计算圆周率的近似值
     * @return 圆周率的近似值
     */

    //	该项目使用以下公式计算圆周率π的近似值，直到某一项的绝对值小于10^(-6)为止。
    //t≈1-1/3+1/5-1/7+⋯
    //其中π=4t。
    public static double calculate() {
            double pi = 0.0;
            double pi_t = 1.0; //初始化第一项为 1
            int fuhao = 1; //初始化符号为正数
            int n = 1; // 初始化项数

            while (Math.abs(pi_t) > Math.pow(10, -6)) {
                pi += fuhao * pi_t / n;
                fuhao = -fuhao;//每次变号
                n += 2; //+2得到奇数分母
                pi_t = (1.0 / n); //计算下一项的分子
            }

            return 4 * pi; //  pi = 4t
        }

}
