#include <jni.h>
#include <string>
#include <android/log.h>

#define Tag "jni"

//返回一个字符串
extern "C" JNIEXPORT jstring JNICALL
Java_com_nk_jnitypetest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//返回一个数字
extern "C"
JNIEXPORT jint JNICALL
Java_com_nk_jnitypetest_MainActivity_intFromJNI(JNIEnv *env, jobject thiz) {
    jint a = 100;
    return 100;
}

//返回传入的字符串，做处理
extern "C"
JNIEXPORT jstring JNICALL
Java_com_nk_jnitypetest_MainActivity_stringFromJNI2(JNIEnv *env, jobject thiz, jstring str) {
    const char *cs = env->GetStringUTFChars(str, 0);
    //也可以直接用string接受
    std::string x = env->GetStringUTFChars(str, 0);
    std::string s = std::string(cs) + " aaa" + x;
    return env->NewStringUTF(s.c_str());
}

//返回传入的数字做处理
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_nk_jnitypetest_MainActivity_intFromJNI2(JNIEnv *env, jobject thiz, jfloat num) {
    float n = 5;
    num += n;
    return num;
}

//返回一个对象 使用无参构造函数
extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objFromJNI(JNIEnv *env, jobject thiz) {
    //获取类型
    jclass cls = env->FindClass("com/nk/jnitypetest/Student");
    //获取构造无参函数
    jmethodID id = env->GetMethodID(cls, "<init>", "()V");
    //获取属性的id
    jfieldID jfage = env->GetFieldID(cls, "age", "I");
    jfieldID jfname = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jfieldID jfisMale = env->GetFieldID(cls, "isMale", "Z");
    //定义一个字符串
    jstring jaa = env->NewStringUTF("张三");
    //类型实例
    jobject obj = env->NewObject(cls, id);
    //设置属性的值
    env->SetIntField(obj,jfage,18);
    env->SetObjectField(obj,jfname,jaa);
    env->SetBooleanField(obj,jfisMale, true);
    //回收不用的值
    env->DeleteLocalRef(jaa);
    return obj;
}

//返回一个对象 使用有参数构造函数
extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objFromJNI2(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/nk/jnitypetest/Student");

    //获取有参构造函数
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");

    jstring jname = env->NewStringUTF("李四");
    //类型实例
    jobject obj = env->NewObject(cls, id, 28, jname, false);
    env->DeleteLocalRef(jname);
    return obj;
}

//返回一个对象数组
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_nk_jnitypetest_MainActivity_arrObjFromJNI(JNIEnv *env, jobject thiz) {
    int length = 5;

    jclass cls = env->FindClass("com/nk/jnitypetest/Student");
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");
    jstring jname = env->NewStringUTF("王五");
    jobjectArray  objArray = env->NewObjectArray(length, cls, nullptr);

    for(int i=0;i<length;i++){
        jobject obj = env->NewObject(cls, id, i, jname,true);
        env->SetObjectArrayElement(objArray, i, obj);
        env->DeleteLocalRef(obj);
    }
    env->DeleteLocalRef(jname);
    return objArray;
}

//返回一个二维对象数组
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_nk_jnitypetest_MainActivity_arrObjFromJNI2(JNIEnv *env, jobject thiz) {
    int len1 = 3;
    int len2 = 4;

    //获取对象
    jclass cls = env->FindClass("com/nk/jnitypetest/Student");
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");
    //获得一维对象数组实例
    jobjectArray objArr = env->NewObjectArray(len1, cls, nullptr);
    //获得一维数组对象的类型
    jclass cla = env->GetObjectClass(objArr);
    env->DeleteLocalRef(objArr);
    //获得二维数组对象的类型
    jobjectArray pArray = env->NewObjectArray(len2, cla, nullptr);

    for(int i=0;i<len2;i++){
        jobjectArray temp = env->NewObjectArray(len1, cls, nullptr);
        for(int j=0;j<len1;j++){
            jstring jname = env->NewStringUTF("赵六");
            jobject obj = env->NewObject(cls, id, j, jname,true);
            env->DeleteLocalRef(jname);

            env->SetObjectArrayElement(temp, j, obj);
            env->DeleteLocalRef(obj);
        }
        env->SetObjectArrayElement(pArray, i, temp);
        env->DeleteLocalRef(temp);
    }
    return pArray;

}


//返回一个ArrayList<Object>
extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_listFromJNI(JNIEnv *env, jobject thiz) {
    int len = 5;

    jclass cls = env->FindClass("com/nk/jnitypetest/Student");
    jmethodID id = env->GetMethodID(cls, "<init>", "(ILjava/lang/String;Z)V");

    jclass cla = env->FindClass("java/util/ArrayList");
    jmethodID idInit = env->GetMethodID(cla, "<init>", "()V");
    jmethodID idAdd = env->GetMethodID(cla, "add", "(Ljava/lang/Object;)Z");

    jobject objList = env->NewObject(cla, idInit);

    for(int i=0;i<len;i++){
        jstring jname = env->NewStringUTF("孙七");
        jobject obj = env->NewObject(cls, id, i, jname,true);
        env->DeleteLocalRef(jname);

        env->CallBooleanMethod(objList,idAdd,obj);
        env->DeleteLocalRef(obj);
    }
    return objList;
}

//传入一个对象 从java向cpp传值
extern "C"
JNIEXPORT void JNICALL
Java_com_nk_jnitypetest_MainActivity_objToJNI(JNIEnv *env, jobject thiz, jobject a) {
    jclass cls = env->GetObjectClass(a);

    jfieldID jfage = env->GetFieldID(cls, "age", "I");
    jfieldID jfname = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jfieldID jfisMale = env->GetFieldID(cls, "isMale", "Z");

    jint ageInt = env->GetIntField(a, jfage);
    jstring nameString = (jstring)env->GetObjectField(a, jfname);
    jboolean isMaleBool = env->GetBooleanField(a, jfisMale);

    const  char * name = env->GetStringUTFChars(nameString, 0);

    __android_log_print(ANDROID_LOG_DEBUG, Tag, "*****测试传入一个对象 从java向cpp传值*****");
    __android_log_print(ANDROID_LOG_DEBUG, Tag, "ageInt:%d",ageInt);
    __android_log_print(ANDROID_LOG_DEBUG, Tag, "name:%s",name);
    __android_log_print(ANDROID_LOG_DEBUG, Tag, "isMaleBool:%d",isMaleBool);

    env->ReleaseStringUTFChars(nameString,name);

    return;
}

//传入一个对象 从cpp向java传值
extern "C"
JNIEXPORT void JNICALL
Java_com_nk_jnitypetest_MainActivity_objToJNI2(JNIEnv *env, jobject thiz, jobject a) {
    jclass cls = env->GetObjectClass(a);

    jfieldID jfage = env->GetFieldID(cls, "age", "I");
    jfieldID jfname = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jfieldID jfisMale = env->GetFieldID(cls, "isMale", "Z");

    jstring name = env->NewStringUTF("objToJNI2");

    env->SetIntField(a, jfage, 100);
    env->SetObjectField(a, jfname, name);
    env->SetBooleanField(a, jfisMale, true);

    env->DeleteLocalRef(name);

    return;
}

//返回一个对象 成员是复杂类型
extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objPorpertyJNI(JNIEnv *env, jobject thiz) {
    jclass clz = env->FindClass("com/nk/jnitypetest/Student");
    jmethodID idz = env->GetMethodID(clz, "<init>", "(ILjava/lang/String;Z)V");
    jstring jname = env->NewStringUTF("钱八");
    jobject obj = env->NewObject(clz, idz, 100, jname,true);
    env->DeleteLocalRef(jname);

    jclass cls = env->FindClass("com/nk/jnitypetest/School");
    jmethodID id = env->GetMethodID(cls, "<init>", "()V");
    //必须要在类型前面加上L，否则无法识别
    jfieldID jfa = env->GetFieldID(cls, "student", "Lcom/nk/jnitypetest/Student;");

    jobject  objb = env->NewObject(cls, id);
    env->SetObjectField(objb, jfa,  obj);
    env->DeleteLocalRef(obj);
    return objb;
}

//返回一个对象 方法的参数是复杂类型
extern "C"
JNIEXPORT jobject JNICALL
Java_com_nk_jnitypetest_MainActivity_objPorpertyJNI2(JNIEnv *env, jobject thiz) {
    jclass clz = env->FindClass("com/nk/jnitypetest/Student");
    jmethodID idz = env->GetMethodID(clz, "<init>", "(ILjava/lang/String;Z)V");
    jstring jname = env->NewStringUTF("objPorpertyJNI2");
    jobject obj = env->NewObject(clz, idz, 500, jname,true);
    env->DeleteLocalRef(jname);

    jclass cls = env->FindClass("com/nk/jnitypetest/School");
    jmethodID id = env->GetMethodID(cls, "<init>", "()V");
    //必须要在类型前面加上L，否则无法识别
    jmethodID jid = env->GetMethodID(cls, "getStudent", "(Lcom/nk/jnitypetest/Student;)Lcom/nk/jnitypetest/Student;");

    jobject  objb = env->NewObject(cls, id);
    jobject objbResult = env->CallObjectMethod(objb, jid, obj);

    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(objb);

    return objbResult;
}
