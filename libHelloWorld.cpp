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

    env->FindClass("HelloWorld");
    env->FindClass("HelloWorld");

    Block *b = (Block *) arg;
    printf("b.name:%s\n", b->name);
    printf("b.jname:%s\n", env->GetStringUTFChars(b->jname, NULL));

    jclass cls = env->FindClass("HelloWorld");
    jmethodID methodID = env->GetStaticMethodID(cls, "test", "(II)I");
    jint val = env->CallStaticIntMethod(cls, methodID, 3, 5);
    printf("call test = %d\n", val);

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
    Block *b = (Block *) malloc(sizeof(Block));
    b->name = "aaaaaaaa";
    b->jname = (jstring) env->NewGlobalRef(env->NewStringUTF("bbbbbbb"));

    printf("main 1\n");

    jclass cls = env->FindClass("HelloWorld");
    jmethodID methodID = env->GetStaticMethodID(cls, "test", "(II)I");
    jint val = env->CallStaticIntMethod(cls, methodID, 3, 5);
    printf("call test = %d\n", val);

    pthread_t t;
    int r;
    r = pthread_create(&t, NULL, PrintHello, (void *)b);
    if (r) {
      printf("thread was't created");
    }

    printf("main 2\n");

    pthread_exit(NULL);

    printf("main 3\n");
    free(b);
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
