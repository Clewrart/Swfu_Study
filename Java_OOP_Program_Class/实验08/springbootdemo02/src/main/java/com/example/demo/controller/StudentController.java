package com.example.demo.controller;

import com.example.demo.dao.StudentDao;
import com.example.demo.entity.Student;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping(value ="/student")
    public class StudentController {
        @Autowired
        private StudentDao studentDao;

        @GetMapping("/getStudents")
        public List<Student> getStudents() {
            return studentDao.queryStudentAll();
        }

        @GetMapping("/getStudent")
        public Student getStudent(@RequestParam Long id) {
            return studentDao.queryStudentByID(id);
        }

        @PutMapping("/updateStudent")
        public int update(@RequestBody Student student) {
            return studentDao.updateStudent(student);
        }

        @PostMapping("/addStudent")
        public int add(@RequestBody Student student) {
            return studentDao.insertStudent(student);
        }

        @DeleteMapping("/deleteStudent/{id}")
        public int delete(@PathVariable("id") Long id) {
            return studentDao.deleteStudentById(id);
        }

        @DeleteMapping("/deleteArea/{startId},{endId}")
        public int delete(@PathVariable("startId") Long startId,@PathVariable("endId") Long endId){
            return studentDao.deleteArea(startId,endId);
        }
    }