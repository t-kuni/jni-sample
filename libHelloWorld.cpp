#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"
#define NUM_THREADS  5

typedef struct {
  char *name;
  jstring jname;
} Block;

static JavaVM *savedVm;

// get saved JavaVM
JavaVM *getVM() {
  return savedVm;
}

// get JNIEnv on current thread
// you should call AttachCurrentThread/AttachCurrentThreadAsDaemon on the thread
// before this function call
JNIEnv *getEnv() {
  JNIEnv *env = NULL;
  if (savedVm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
    env = NULL;
  }
  return env;
}

void *PrintHello(void *arg)
{
  printf("thread 1\n");

  JavaVM *vm = getVM();
  if (vm) {
    printf("thread 2\n");
    JNIEnv *env;

    vm->AttachCurrentThread((void **)&env, NULL);

    Block *b = (Block *) arg;
    printf("b.name:%s\n", b->name);
    printf("b.jname:%s\n", env->GetStringUTFChars(b->jname, NULL));

    vm->DetachCurrentThread();
  } else {
    printf("nothing vm\n");
  }

  printf("thread 3\n");

  pthread_exit(NULL);
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    Block b;
    b.name = "aaaaaaaa";
    b.jname = (jstring) env->NewGlobalRef(env->NewStringUTF("bbbbbbb"));

    printf("main 1\n");

    pthread_t t;
    pthread_create(&t, NULL, PrintHello, (void *)&b);

    printf("main 2\n");

    pthread_exit(NULL);

    printf("main 3\n");
    return;
}

jint JNI_OnLoad(JavaVM *vm, void *aa) {
  JNIEnv *env;
  if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }
  // save and hold pointer to JavaVM
  savedVm = vm;
  // register native functions and/or initialize native codes here if you need
  return JNI_VERSION_1_6;
}
