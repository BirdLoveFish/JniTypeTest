package com.nk.jnitypetest;

public class Student extends Object{

    public Student(){

    }

    public Student(int age, String name, boolean isMale){
        this.age = age;
        this.name = name;
        this.isMale = isMale;
    }

    public int age;
    public String name;
    public boolean isMale;
}