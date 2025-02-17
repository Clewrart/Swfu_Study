package com.example.demo.entity;
import lombok.Data;

import java.security.PrivilegedAction;

    @Data
    public class Student{
        private Long id;
        private Long classId;
        private String name;
        private String gender;
        private Long score;
    }
