package org.example.util;

import org.example.Demo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Util {
    /**
     * 读取保存在resources目录下面的JSON文件
     * @param jsonFileName JSON文件名
     * @return 字符串形式的JSON内容
     */
    public static String readJsonFile(final String jsonFileName) {
        String jsonStr = null;

        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(
                        Demo.class.getClassLoader().getResourceAsStream(jsonFileName)))) {
            StringBuilder stringBuffer = new StringBuilder();
            String str;

            while ((str = br.readLine()) != null) {
                stringBuffer.append(str);
            }

            jsonStr = stringBuffer.toString();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return jsonStr;
    }
}
