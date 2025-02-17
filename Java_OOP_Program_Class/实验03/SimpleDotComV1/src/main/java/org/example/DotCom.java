package org.example;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

/**
 * DotCom类
 */
public class DotCom {
    //private int[] locations;
    // 位置坐标
    private ArrayList<Integer> locations = new ArrayList<>();

    private int numOfHits;    // 猜中次数

    /**
     * 构造函数
     */
    public DotCom(int bound) {
        Random random = new Random();
        int num = random.nextInt(bound);
        //locations = new int[]{ num, num + 1, num + 2 };
        locations.add(num);
        locations.add(num+1);
        locations.add(num+2);
    }
    /**
     * 检查用户输入
     * @param guess 用户输入
     * @return 猜测结果
     */
    public EGameResult checkUserGuess(int guess) {

        EGameResult result = EGameResult.MISS;

    //找位置
        /*
        for( int e : locations){
            if (guess == e) {
                result = EGameResult.HIT;
                numOfHits +=1;
                break;
            }
        }
        */
        //命中即删除
        if(locations.contains(guess)){
            locations.remove((Integer) guess);
            result = EGameResult.HIT;
        }


        //全中,numOfHits =坐标数组长度
       // if (numOfHits == locations.length){


            result = EGameResult.DUNK;
        }
        return result;
    }
}
