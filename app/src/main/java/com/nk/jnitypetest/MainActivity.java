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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        //        Log.d("jni", "onCreate: " + stringFromJNI());

//        String str = "wowo";
//        Log.d("jni", "onCreate: " + stringFromJNI2(str));
//        Log.d("jni", "onCreate: " + str);

//        Log.d("jni", "onCreate: " + intFromJNI());

//        Log.d("jni", "onCreate: " + intFromJNI2(100));

//        Log.d("jni", "onCreate: " + objFromJNI().a);
//        Log.d("jni", "onCreate: " + objFromJNI().aa);
//        Log.d("jni", "onCreate: " + objFromJNI().aaa);
//
//        Log.d("jni", "onCreate: " + objFromJNI2().a);
//        Log.d("jni", "onCreate: " + objFromJNI2().aa);
//        Log.d("jni", "onCreate: " + objFromJNI2().aaa);

//        A[] aArray = arrObjFromJNI();
//        aArray[0].aa = "bbb";
//        for(A arr : aArray){
//            Log.d("jni", "onCreate: " + arr.a);
//            Log.d("jni", "onCreate: " + arr.aa);
//            Log.d("jni", "onCreate: " + arr.aaa);
//        }

//        A[][] aArrArray = arrObjFromJNI2();
//        for(A[] aArr : aArrArray){
//            for(A arr : aArr){
//                Log.d("jni", "onCreate: " + arr.a);
//                Log.d("jni", "onCreate: " + arr.aa);
//                Log.d("jni", "onCreate: " + arr.aaa);
//            }
//        }

//        ArrayList<A> aList = listFromJNI();
//        for (A arr: aList) {
//                Log.d("jni", "onCreate: " + arr.a);
//                Log.d("jni", "onCreate: " + arr.aa);
//                Log.d("jni", "onCreate: " + arr.aaa);
//        }

//        A a = new A(6,"aa",true);
//        objToJNI(a);

//        A a = new A();
//        objToJNI2(a);
//        Log.d("jni", "onCreate: " + a.a);
//        Log.d("jni", "onCreate: " + a.aa);
//        Log.d("jni", "onCreate: " + a.aaa);

//        B b = objPorpertyJNI();
//        Log.d("jni", "onCreate: " + b.a.a);
//        Log.d("jni", "onCreate: " + b.a.aa);
//        Log.d("jni", "onCreate: " + b.a.aaa);

        B b = objPorpertyJNI();
        b.a = new A(99,"ddd",true);
        A a = b.Fun(b.a);
        Log.d("jni", "onCreate: " + a.a);
        Log.d("jni", "onCreate: " + a.aa);
        Log.d("jni", "onCreate: " + a.aaa);


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
    public native A objFromJNI();

    //返回一个对象 使用有参数构造函数
    public native A objFromJNI2();

    //返回一个对象数组
    public native A[] arrObjFromJNI();

    //返回一个二维对象数组
    public native A[][] arrObjFromJNI2();

    //返回一个ArrayList<Object>
    public native ArrayList<A> listFromJNI();

    //传入一个对象 从java向cpp传值
    public native void objToJNI(A a);

    //传入一个对象 从cpp向java传值
    public native void objToJNI2(A a);

    //返回一个对象 成员是复杂类型
    public native B objPorpertyJNI();

    //返回一个对象 方法的参数是复杂类型
    public native B objPorpertyJNI2();
}
