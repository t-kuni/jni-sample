#include <pthread.h>
#include <stdio.h>
#include "HelloWorld.h"

static JavaVM *savedVm;

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    jint version = env->GetVersion();
    printf("Hello World! JNI(version:%d)\n", version);
    return;
}

jint JNI_OnLoad(JavaVM *vm, void *aa) {
  savedVm = vm;
  printf("Called JNI_OnLoad\n");
	// JNIEnv *env;
	// if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
	// 	return JNI_ERR;
	// }
	// // save and hold pointer to JavaVM
	// savedVm = vm;
	// // register native functions and/or initialize native codes here if you need
	return JNI_VERSION_1_6;
}
