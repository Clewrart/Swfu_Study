package org.example;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import org.example.entity.BookBean;
import org.example.util.Util;

import java.util.List;

public class Demo {
    public static void main(String[] args) {
        String jsonFileName = "data.json";
        Gson gson = new Gson();
        String jsonStr = Util.readJsonFile(jsonFileName);

        System.out.println("方式一：使用数组");
        if (jsonStr != null) {
            BookBean[] bookBeans = gson.fromJson(jsonStr, BookBean[].class);
            for (BookBean book : bookBeans) {
                System.out.println(book);
            }
        }
        else{
            System.out.println("错误数据！");
        }


        System.out.println("方式二：使用反射");
        if (jsonStr != null) {
            TypeToken<List<BookBean>> typeToken = new TypeToken<List<BookBean>>(){};
            List<BookBean> bookBeans = gson.fromJson(jsonStr, typeToken.getType());
            for (BookBean book : bookBeans) {
                System.out.println(book);
        }
            }
        else{
            System.out.println("错误数据！");
        }
    }
}