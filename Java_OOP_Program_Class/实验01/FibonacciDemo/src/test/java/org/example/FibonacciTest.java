package org.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class FibonacciTest {

    @Test
    void compute() {
            int ex_test1 = 7;//参考1
            int[] aw_test1 = {0,1,1,2,3,5,8};//参考结果1
            Fibonacci fibonacci_test = new Fibonacci();//测试方法
            int[] check1 = fibonacci_test.compute(ex_test1);
            assertArrayEquals(aw_test1,check1);//断言判定


        }
    }