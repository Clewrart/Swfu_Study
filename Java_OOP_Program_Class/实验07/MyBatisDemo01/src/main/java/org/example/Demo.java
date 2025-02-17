package org.example;

import org.apache.ibatis.session.SqlSession;
import org.example.dao.StudentDao;
import org.example.entity.Student;
import org.example.util.SqlSessionFactoryUtil;

import java.util.List;

public class Demo {
    public static void main(String[] args) {
        try (SqlSession sqlSession = SqlSessionFactoryUtil.getSqlSessionFactory().openSession(true)) {
            // 添加测试代码
            final StudentDao studentDao = sqlSession.getMapper(StudentDao.class);
            System.out.println("添加一条新的学生记录");
            Student student = new Student();
            student.setClassId(3L);
            student.setName("王泉");
            student.setGender("M");
            student.setScore(81.5);

            studentDao.insertStudent(student);

            System.out.println("对数据表进行查询");
            final List<Student> studentList = studentDao.queryStudentAll();
            for(Student stud : studentList) {
                System.out.println(stud);
            }
        }
    }
}
