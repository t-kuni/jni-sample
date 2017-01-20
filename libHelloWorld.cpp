#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"
#define NUM_THREADS	5

static JavaVM *savedVm;

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    jint version = env->GetVersion();
    printf("Hello World! JNI(version:%d)\n", version);

    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0;t<NUM_THREADS;t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
        }
      }

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
