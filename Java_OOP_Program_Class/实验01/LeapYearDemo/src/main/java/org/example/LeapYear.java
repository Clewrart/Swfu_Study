package org.example;

/**
 * 闰年类
 */
public class LeapYear {
    /**
     * 判断一个年份是否是闰年。
     * 判断一个年份是否是闰年的算法为：1) 能够被4整除，但不能被100整除；2) 能被400整除。
     * @param year 年份
     * @return 如果year是闰年，返回true；否则返回false。

    */

    public static boolean isLeapYear(int year) {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                // 能被100整除，需能被400整除
                return year % 400 == 0;
            } else {
                // 不被100整除，直闰年
                return true;
            }
        } else {
            // 不被4整除，不是闰年
            return false;
        }
    }
}