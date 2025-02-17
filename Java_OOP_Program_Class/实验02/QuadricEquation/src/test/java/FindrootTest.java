import org.example.QuadricEquation;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class FindrootTest {

    @Test
    void test1() {
        double[] eg_test1 = {1.0, -1.0, 2.0};//用例1
        double[] aw_test1 = null;//参考结果1

        QuadricEquation findrootTest1 = new QuadricEquation(eg_test1[0], eg_test1[1], eg_test1[2]);//测试方法
        double[] check1 = findrootTest1.findRoot();
        assertEquals(aw_test1, check1);//断言判定
    }

    @Test
    void test2() {

        double[] eg_test2 = {9.0, -6.0, 1.0};//用例2
        double[] aw_test2 = {0.33333};//参考结果2
        QuadricEquation findrootTest2 = new QuadricEquation(eg_test2[0], eg_test2[1], eg_test2[2]);//测试方法
        double[] check2 = findrootTest2.findRoot();
        assertArrayEquals(aw_test2, check2, 0.001);//断言判定带精度

    }

    @Test
    void test3(){
        double[] eg_test3 = {1.0, -2.0, -3.0};//用例3
        double[] aw_test3 = {3.0, -1.0};//参考结果3
        QuadricEquation findrootTest3 = new QuadricEquation(eg_test3[0], eg_test3[1], eg_test3[2]);//测试方法
        double[] check3 = findrootTest3.findRoot();
        assertArrayEquals(aw_test3, check3);//断言判定

    }
}
