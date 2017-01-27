#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"
#include <unistd.h>
#define NUM_THREADS  5

void *PrintHello(void *arg)
{
  const char *msg = (const char *) arg;

  printf("thread run[name:%s]\n", msg);

  sleep(4);

  printf("thread end\n");

  pthread_exit(NULL);
}

void run(pthread_mutex_t *mutex, const char *msg) {
    pthread_t t;
    pthread_create(&t, NULL, PrintHello, (void *)msg);
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    printf("main start\n");

    static pthread_mutex_t mutex;

    run(&mutex, "A");
    sleep(5);

    pthread_exit(NULL);

    printf("main end\n");
    return;
}
