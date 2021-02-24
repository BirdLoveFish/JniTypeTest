package com.nk.jnitypetest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private String Tag = "jni";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

         /*
         *      测试返回一个字符串
         *
         * */
        Log.d(Tag, "*****测试返回一个字符串*****");
        Log.d(Tag, "返回的字符串为: " + stringFromJNI());
        Log.d(Tag, "\n");

        /*
         *      测试对传入的字符串进行处理
         *
         * */
        Log.d(Tag, "*****测试对传入的字符串进行处理*****");
        String str = "wowo";
        Log.d(Tag, "原始的字符串为: " + str);
        Log.d(Tag, "修改后的字符串为: " + stringFromJNI2(str));
        Log.d(Tag, "\n");

        /*
         *      测试返回一个数字
         *
         * */
        Log.d(Tag, "*****测试返回一个数字*****");
        Log.d(Tag, "返回的数字为: " + intFromJNI());
        Log.d(Tag, "\n");

        /*
         *      测试对传入的数字进行处理
         *
         * */
        Log.d(Tag, "*****测试对传入的数字进行处理*****");
        int num = 100;
        Log.d(Tag, "原始的数字:为 " + num);
        Log.d(Tag, "修改后的数字为: " + intFromJNI2(num));
        Log.d(Tag, "\n");

        /*
         *      测试使用有参数构造函数返回一个对象
         *
         * */
        Log.d(Tag, "*****测试使用无参构造函数返回一个对象*****");
        Log.d(Tag, "对象的age: " + objFromJNI().age);
        Log.d(Tag, "对象的name: " + objFromJNI().name);
        Log.d(Tag, "对象的isMale: " + objFromJNI().isMale);
        Log.d(Tag, "\n");

        /*
         *      测试使用无参构造函数返回一个对象
         *
         * */
        Log.d(Tag, "*****测试使用无参构造函数返回一个对象*****");
        Log.d(Tag, "对象的age: " + objFromJNI2().age);
        Log.d(Tag, "对象的name: " + objFromJNI2().name);
        Log.d(Tag, "对象的isMale: " + objFromJNI2().isMale);
        Log.d(Tag, "\n\n");

        /*
         *      测试返回一个二维对象数组
         *
         * */
        Log.d(Tag, "*****测试返回一个对象数组*****");
        Student[] stuArray = arrObjFromJNI();
        for(Student student : stuArray){
            Log.d(Tag, "对象的age: " + student.age);
            Log.d(Tag, "对象的name: " + student.name);
            Log.d(Tag, "对象的isMale: " + student.isMale);
        }

        /*
         *      测试返回一个二维对象数组
         *
         * */
        Log.d(Tag, "*****返回一个二维对象数组*****");
        Student[][] stuArrArray = arrObjFromJNI2();
        for(Student[] stuArr : stuArrArray){
            for(Student stu : stuArr){
                Log.d(Tag, "对象的age: " + stu.age);
                Log.d(Tag, "对象的name: " + stu.name);
                Log.d(Tag, "对象的isMale: " + stu.isMale);
            }
        }

        /*
         *      测试返回一个ArrayList<Object>
         *
         * */
        Log.d(Tag, "*****测试返回一个ArrayList<Object>*****");
        ArrayList<Student> stuList = listFromJNI();
        for (Student stu: stuList) {
                Log.d(Tag, "对象的age: " + stu.age);
                Log.d(Tag, "对象的name: " + stu.name);
                Log.d(Tag, "对象的isMale: " + stu.isMale);
        }

        /*
         *      测试传入一个对象 从java向cpp传值
         *
         * */
        Student stuObjToJNI= new Student(6,"aa",true);
        objToJNI(stuObjToJNI);

        /*
         *      测试传入一个对象 从cpp向java传值
         *
         * */
        Log.d(Tag, "*****测试传入一个对象 从cpp向java传值*****");
        Student stuObjToJNI2 = new Student();
        objToJNI2(stuObjToJNI2);
        Log.d(Tag, "对象的age: " + stuObjToJNI2.age);
        Log.d(Tag, "对象的name: " + stuObjToJNI2.name);
        Log.d(Tag, "对象的isMale: " + stuObjToJNI2.isMale);

        /*
         *      返回一个对象 成员是复杂类型
         *
         * */
        Log.d(Tag, "*****返回一个对象 成员是复杂类型*****");
        School school1 = objPorpertyJNI();
        Log.d(Tag, "对象的age: " + school1.student.age);
        Log.d(Tag, "对象的name: " + school1.student.name);
        Log.d(Tag, "对象的isMale: " + school1.student.isMale);

        /*
         *      返回一个对象 方法的参数是复杂类型
         *
         * */
//        Log.d(Tag, "*****返回一个对象 方法的参数是复杂类型*****");
//        School school2 = objPorpertyJNI2();
//        school2.student = new Student(99,"ddd",true);
//        Student stu = school2.getStudent(school1.student);
//        Log.d(Tag, "对象的age: " + stu.age);
//        Log.d(Tag, "对象的name: " + stu.name);
//        Log.d(Tag, "对象的isMale: " + stu.isMale);

        Log.d(Tag, "*****返回一个对象 方法的参数是复杂类型*****");
        Student stuObjPorpertyJNI2 = objPorpertyJNI2();
        Log.d(Tag, "对象的age: " + stuObjPorpertyJNI2.age);
        Log.d(Tag, "对象的name: " + stuObjPorpertyJNI2.name);
        Log.d(Tag, "对象的isMale: " + stuObjPorpertyJNI2.isMale);


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    //返回一个字符串
    public native String stringFromJNI();

    //返回传入的字符串，做处理
    public native String stringFromJNI2(String str);

    //返回一个数字
    public native int intFromJNI();

    //返回传入的数字做处理
    public native float intFromJNI2(float num);

    //返回一个对象 使用无参构造函数
    public native Student objFromJNI();

    //返回一个对象 使用有参数构造函数
    public native Student objFromJNI2();

    //返回一个对象数组
    public native Student[] arrObjFromJNI();

    //返回一个二维对象数组
    public native Student[][] arrObjFromJNI2();

    //返回一个ArrayList<Object>
    public native ArrayList<Student> listFromJNI();

    //传入一个对象 从java向cpp传值
    public native void objToJNI(Student student);

    //传入一个对象 从cpp向java传值
    public native void objToJNI2(Student student);

    //返回一个对象 成员是复杂类型
    public native School objPorpertyJNI();

    //返回一个对象 方法的参数是复杂类型
    public native Student objPorpertyJNI2();
}
