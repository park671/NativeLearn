#include <jni.h>
#include "native_add.h"

extern "C" int add(int a, int b);
extern "C" int add_opt(int a, int b);

asm(".globl add\n"
    "add:\n" //入参分别存储在 w0 w1上 （以此类推存储在wn上）
    "sub\tsp, sp, #16\n"   //进入函数，调整栈顶位置
    "str\tw0, [sp, #12]\n" //把w0寄存器存放到内存栈偏移12的位置上
    "str\tw1, [sp, #8]\n"  //把w1寄存器存放到内存栈品偏移8的位置上
    "ldr\tw8, [sp, #12]\n" //把 内存栈偏移12的位置上 的数据存储到w8
    "ldr\tw9, [sp, #8]\n"  //把 内存栈偏移8的位置上 的数据存储到w9
    "add\tw0, w8, w9\n"    //相加w8 w9，结果存放在w0
    "add\tsp, sp, #16\n"   //退出函数，恢复栈顶位置
    "ret\n");

asm(".globl add_opt\n"
    "add_opt:\n" //入参分别存储在 w0 w1上 （以此类推存储在wn上）
    "add\tw0, w1, w0\n"    //相加w0 w1，结果存放在w0
    "ret\n");

extern "C"
JNIEXPORT jstring JNICALL
Java_com_park_native_1learn_NativeBridge_getInfoFromNative(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("hello world from native c++!");
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_park_native_1learn_NativeBridge_addCpp(JNIEnv *env, jobject thiz, jint a, jint b) {
    int c = a+b;
    return c;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_park_native_1learn_NativeBridge_addInlineAsm(JNIEnv *env, jobject thiz, jint a, jint b) {
    return add(a, b);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_park_native_1learn_NativeBridge_addAsm(JNIEnv *env, jobject thiz, jint a, jint b) {
    return add_asm(a, b);
}