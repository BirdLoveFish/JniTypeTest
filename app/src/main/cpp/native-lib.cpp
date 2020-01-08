#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_nk_jnitypetest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_nk_jnitypetest_MainActivity_intFromJNI(JNIEnv *env, jobject thiz) {
    jint a = 100;
    return 100;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_nk_jnitypetest_MainActivity_stringFromJNI2(JNIEnv *env, jobject thiz, jstring str) {
    const char *cs = env->GetStringUTFChars(str, 0);
    //也可以直接用string接受
    std::string x = env->GetStringUTFChars(str, 0);
    std::string s = std::string(cs) + " aaa" + x;
    return env->NewStringUTF(s.c_str());
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_nk_jnitypetest_MainActivity_intFromJNI2(JNIEnv *env, jobject thiz, jfloat num) {
    float n = 5;
    num += n;
    return num;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objFromJNI(JNIEnv *env, jobject thiz) {
    //获取类型
    jclass cls = env->FindClass("com/nk/jnitypetest/A");
    //获取构造无参函数
    jmethodID id = env->GetMethodID(cls, "<init>", "()V");
    //获取属性的id
    jfieldID jfa = env->GetFieldID(cls, "a", "I");
    jfieldID jfaa = env->GetFieldID(cls, "aa", "Ljava/lang/String;");
    jfieldID jfaaa = env->GetFieldID(cls, "aaa", "Z");
    //定义一个字符串
    jstring jaa = env->NewStringUTF("aa");
    //类型实例
    jobject obj = env->NewObject(cls, id, nullptr);
    //设置属性的值
    env->SetIntField(obj,jfa,1);
    env->SetObjectField(obj,jfaa,jaa);
    env->SetBooleanField(obj,jfaaa, true);
    //回收不用的值
    env->DeleteLocalRef(jaa);
    return obj;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objFromJNI2(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/nk/jnitypetest/A");

    //获取有参构造函数
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");

    jstring jaa = env->NewStringUTF("aa2");
    //类型实例
    jobject obj = env->NewObject(cls, id, 2,jaa,true);
    env->DeleteLocalRef(jaa);
    return obj;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_nk_jnitypetest_MainActivity_arrObjFromJNI(JNIEnv *env, jobject thiz) {

    jclass cls = env->FindClass("com/nk/jnitypetest/A");
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");
    jstring jaa = env->NewStringUTF("aa2");
    jobjectArray  objArray = env->NewObjectArray(10, cls, nullptr);

    for(int i=0;i<10;i++){
        jobject obj = env->NewObject(cls, id, i, jaa,true);
        env->SetObjectArrayElement(objArray, i, obj);
        env->DeleteLocalRef(obj);
    }
    env->DeleteLocalRef(jaa);
    return objArray;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_nk_jnitypetest_MainActivity_arrObjFromJNI2(JNIEnv *env, jobject thiz) {
    //获取对象
    jclass cls = env->FindClass("com/nk/jnitypetest/A");
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");
    //获得一维对象数组实例
    jobjectArray objArr = env->NewObjectArray(5, cls, nullptr);
    //获得一维数组对象的类型
    jclass cla = env->GetObjectClass(objArr);
    env->DeleteLocalRef(objArr);
    //获得二维数组对象的类型
    jobjectArray pArray = env->NewObjectArray(5, cla, nullptr);


    for(int i=0;i<5;i++){
        jobjectArray temp = env->NewObjectArray(5, cls, nullptr);
        for(int j=0;j<5;j++){
            jstring jaa = env->NewStringUTF("aa2");
            jobject obj = env->NewObject(cls, id, j, jaa,true);
            env->DeleteLocalRef(jaa);

            env->SetObjectArrayElement(temp, j, obj);
            env->DeleteLocalRef(obj);
        }
        env->SetObjectArrayElement(pArray, i, temp);
        env->DeleteLocalRef(temp);
    }
    return pArray;

}



extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_listFromJNI(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/nk/jnitypetest/A");
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");

    jclass cla = env->FindClass("java/util/ArrayList");
    jmethodID idInit = env->GetMethodID(cla, "<init>", "()V");
    jmethodID idAdd = env->GetMethodID(cla, "add", "(Ljava/lang/Object;)Z");

    jobject objList = env->NewObject(cla, idInit, nullptr);

    for(int i=0;i<5;i++){
        jstring jaa = env->NewStringUTF("aa2");
        jobject obj = env->NewObject(cls, id, i, jaa,true);
        env->DeleteLocalRef(jaa);

        env->CallObjectMethod(objList,idAdd,obj);
        env->DeleteLocalRef(obj);
    }
    return objList;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nk_jnitypetest_MainActivity_objToJNI(JNIEnv *env, jobject thiz, jobject a) {
    jclass cls = env->GetObjectClass(a);

    jfieldID jfa = env->GetFieldID(cls, "a", "I");
    jfieldID jfaa = env->GetFieldID(cls, "aa", "Ljava/lang/String;");
    jfieldID jfaaa = env->GetFieldID(cls, "aaa", "Z");

    jint aInt = env->GetIntField(a, jfa);
    jstring aaString = (jstring)env->GetObjectField(a, jfaa);
    jboolean aaaBool = env->GetBooleanField(a, jfaaa);

    const  char * aa = env->GetStringUTFChars(aaString, 0);

    __android_log_print(ANDROID_LOG_DEBUG, "jni","aInt:%d",aInt);
    __android_log_print(ANDROID_LOG_DEBUG, "jni","aaString:%s",aa);
    __android_log_print(ANDROID_LOG_DEBUG, "jni","aaaBool:%d",aaaBool);

    env->ReleaseStringUTFChars(aaString,aa);

    return;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nk_jnitypetest_MainActivity_objToJNI2(JNIEnv *env, jobject thiz, jobject a) {
    jclass cls = env->GetObjectClass(a);

    jfieldID jfa = env->GetFieldID(cls, "a", "I");
    jfieldID jfaa = env->GetFieldID(cls, "aa", "Ljava/lang/String;");
    jfieldID jfaaa = env->GetFieldID(cls, "aaa", "Z");

    jstring aa = env->NewStringUTF("objToJNI2");

    env->SetIntField(a, jfa, 100);
    env->SetObjectField(a, jfaa, aa);
    env->SetBooleanField(a, jfaaa, true);

    env->DeleteLocalRef(aa);

    return;
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objPorpertyJNI(JNIEnv *env, jobject thiz) {
    jclass clz = env->FindClass("com/nk/jnitypetest/A");
    jmethodID idz = env->GetMethodID(clz, "<init>", "(ILjava/lang/String;Z)V");
    jstring jaa = env->NewStringUTF("aa2");
    jobject obj = env->NewObject(clz, idz, 100, jaa,true);
    env->DeleteLocalRef(jaa);

    jclass cls = env->FindClass("com/nk/jnitypetest/B");
    jmethodID id = env->GetMethodID(cls, "<init>", "()V");
    //必须要在类型前面加上L，否则无法识别
    jfieldID jfa = env->GetFieldID(cls, "a", "Lcom/nk/jnitypetest/A;");

    jobject  objb = env->NewObject(cls, id);
    env->SetObjectField(objb, jfa,  obj);
    env->DeleteLocalRef(obj);
    return objb;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objPorpertyJNI2(JNIEnv *env, jobject thiz) {
    jclass clz = env->FindClass("com/nk/jnitypetest/A");
    jmethodID idz = env->GetMethodID(clz, "<init>", "(ILjava/lang/String;Z)V");
    jstring jaa = env->NewStringUTF("aa2");
    jobject obj = env->NewObject(clz, idz, 100, jaa,true);
    env->DeleteLocalRef(jaa);

    jclass cls = env->FindClass("com/nk/jnitypetest/B");
    jmethodID id = env->GetMethodID(cls, "<init>", "()V");
    //必须要在类型前面加上L，否则无法识别
    jmethodID jid = env->GetMethodID(cls, "Fun", "(Lcom/nk/jnitypetest/A;)Lcom/nk/jnitypetest/A;");

    jobject  objb = env->NewObject(cls, id);
    jobject objbResult = env->CallObjectMethod(objb, jid, obj);

    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(objb);

    return objbResult;
}
