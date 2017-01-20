#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    jint version = env->GetVersion();
    printf("Hello World! JNI(version:%d)\n", version);
    return;
}
