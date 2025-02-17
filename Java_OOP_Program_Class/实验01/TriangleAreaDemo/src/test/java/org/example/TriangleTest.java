package org.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class TriangleTest {

    @Test
    void area() {
        double[] eg_test1 = {2.7, 3.2, 1.5};//用例1
        double[] aw_test1 = {2.0174241001832014};//参考结果1
        Triangle triangle_test1 = new Triangle(eg_test1[0], eg_test1[1], eg_test1[2]);//测试方法
        double check1 = triangle_test1.area();
        assertEquals(aw_test1[0], check1);//断言判定

        double[] eg_test2 = {3.0, 4.0, 5.0};//用例2
        double[] aw_test2 = {6.0};//参考结果2
        Triangle triangle_test2 = new Triangle(eg_test2[0], eg_test2[1], eg_test2[2]);//测试方法
        double check2 = triangle_test2.area();
        assertEquals(aw_test2[0], check2);//断言判定
    }
}

