package org.example.dao;
import org.example.entity.Student;
import java.util.List;

public interface StudentDao {
    Student queryStudentByID(Long id);
    List<Student> queryStudentAll();
    Integer insertStudent(Student student);
    Integer updateStudent(Student student);
    Integer deleteStudentById(Long id);


}
