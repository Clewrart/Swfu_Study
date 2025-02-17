package org.example.entity;

import java.util.List;

/**
 * 书籍实体类
 */
public class BookBean {
    private Integer id;
    private String name;
    private List<String> authors;
    private String isbn;
    private List<String> tags;
    private Double price;

    @Override
    public String toString() {
        return "BookBean{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", authors=" + authors +
                ", isbn='" + isbn + '\'' +
                ", tags=" + tags +
                ", price=" + price +
                '}';
    }
}
