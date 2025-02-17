package org.example;

import com.google.gson.Gson;
import org.example.entity.*;
import org.example.util.Util;
public class Demo {
    public static void main(String[] args) {
        String jsonFileName = "data.json";
        Gson gson = new Gson();
        String jsonStr = Util.readJsonFile(jsonFileName);

        if (jsonStr != null) {
            // 使用Gson将JSON转换为BookBean对象
            BookBean bookBean = gson.fromJson(jsonStr, BookBean.class);
            System.out.println(bookBean);
        } else {
            System.out.println("错误数据！");
        }
    }
}
