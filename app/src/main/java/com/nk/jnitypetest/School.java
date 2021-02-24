package com.nk.jnitypetest;

import com.nk.jnitypetest.Student;

public class School extends Object {

    public School(){

    }

    public Student student;

    public Student getStudent(Student stu){
        stu.age = 38;
        stu.name = "四九";
        stu.isMale = false;
        return stu;
    }

}
