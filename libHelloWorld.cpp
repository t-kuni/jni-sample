#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    printf("main 1\n");

    jclass cls = env->FindClass("HelloWorld");
    jmethodID methodID = env->GetStaticMethodID(cls, "test", "(II)I");
    jint val = env->CallStaticIntMethod(cls, methodID, 3, 5);
    printf("call test = %d\n", val);

    printf("main 2\n");
}
