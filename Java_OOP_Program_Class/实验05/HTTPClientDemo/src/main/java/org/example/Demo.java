package org.example;

import com.google.gson.Gson;
import org.example.entity.BookBean;

public class Demo {
    public static void main(String[] args) {
        final String url = "http://127.0.0.1";
        final int port = 8899;

        String result = MyHTTPClient.doGet(url + ":" + port);

        if (null != result) {
            Gson gson = new Gson();
            BookBean bookBean = gson.fromJson(result, BookBean.class);
            System.out.println(bookBean);
        }
    }
}