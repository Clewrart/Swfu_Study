CREATE DATABASE IF NOT EXISTS student CHARSET utf8;
USE student;

DROP TABLE IF EXISTS classes;
CREATE TABLE classes (
    id              BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name            VARCHAR(10) NOT NULL
) CHARSET utf8;

DROP TABLE IF EXISTS students;
CREATE TABLE students (
    id              BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    class_id        BIGINT NOT NULL,
    name            VARCHAR(10) NOT NULL,
    gender          CHAR(1) NOT NULL,
    score           BIGINT NOT NULL
) CHARSET utf8;

INSERT INTO classes (name) VALUES ('一班');
INSERT INTO classes (name) VALUES ('二班');
INSERT INTO classes (name) VALUES ('三班');
INSERT INTO classes (name) VALUES ('四班');

INSERT INTO students (class_id, name, gender, score) VALUES (1, '李晓明', 'M', 90);
INSERT INTO students (class_id, name, gender, score) VALUES (1, '范雨虹', 'F', 95);
INSERT INTO students (class_id, name, gender, score) VALUES (1, '张建军', 'M', 88);
INSERT INTO students (class_id, name, gender, score) VALUES (1, '钱丽娟', 'F', 73);
INSERT INTO students (class_id, name, gender, score) VALUES (1, '王晓红', 'F', 81);
INSERT INTO students (class_id, name, gender, score) VALUES (2, '陈立斌', 'M', 55);
INSERT INTO students (class_id, name, gender, score) VALUES (2, '周同林', 'M', 83);
INSERT INTO students (class_id, name, gender, score) VALUES (3, '许耀丹', 'F', 91);
INSERT INTO students (class_id, name, gender, score) VALUES (3, '郭松涛', 'M', 89);
INSERT INTO students (class_id, name, gender, score) VALUES (3, '刘莉莉', 'F', 88);
INSERT INTO students (class_id, name, gender, score) VALUES (4, '孙雨彤', 'F', 77);
INSERT INTO students (class_id, name, gender, score) VALUES (4, '肖战波', 'M', 51);
INSERT INTO students (class_id, name, gender, score) VALUES (4, '韩雨帆', 'F', 68);
