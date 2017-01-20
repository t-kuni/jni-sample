#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"
#define NUM_THREADS	5

struct _Block {
  char *name;
  jstring jname;
} Block;

static JavaVM *savedVm;

void *PrintHello(void *threadid)
{
   printf("called other thread\n");
   pthread_exit(NULL);
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    pthread_t t;
    printf("In main: creating thread %ld\n", t);
    pthread_create(&t, NULL, PrintHello, NULL);

    /* Last thing that main() should do */
    pthread_exit(NULL);
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
