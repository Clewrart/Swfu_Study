package org.example;


import org.apache.hc.client5.http.classic.methods.HttpGet;
import org.apache.hc.client5.http.impl.classic.CloseableHttpClient;
import org.apache.hc.client5.http.impl.classic.CloseableHttpResponse;
import org.apache.hc.client5.http.impl.classic.HttpClients;
import org.apache.hc.core5.http.HttpEntity;
import org.apache.hc.core5.http.ParseException;
import org.apache.hc.core5.http.io.entity.EntityUtils;

import java.io.IOException;

/**
 * 基于Apache HttpClient库创建HTTP客户端用于HTTP服务访问
 * <a href="https://hc.apache.org/httpcomponents-client-5.3.x/index.html">Apache HttpClient</a>
 */
public class MyHTTPClient {
    public static String doGet(String url) {
        String result = null;

        // 使用HttpClients创建一个HttpClient对象
        try (final CloseableHttpClient httpClient = HttpClients.createDefault()) {
            // 创建HttpGet对象以发送GET请求
            HttpGet httpGet = new HttpGet(url);

            // 通过HttpClient对象的execute方法发送GET请求
            result = httpClient.execute(httpGet, response -> {
                // 通过响应对象获取到返回数据的实体对象
                // 并将返回数据的实体对象转换为字符串
                return EntityUtils.toString(response.getEntity());
            });
        } catch (IOException e) {
            return null;
        }

        return result;
    }
}
