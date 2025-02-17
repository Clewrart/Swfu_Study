package com.example.demo.dao;

import com.example.demo.entity.Student;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
    public interface StudentDao {
        Student queryStudentByID(Long id);
        List<Student> queryStudentAll();
        Integer insertStudent(Student student);
        Integer updateStudent(Student student);
        Integer deleteStudentById(Long id);
        Integer deleteArea(Long startId,Long endId);

}
