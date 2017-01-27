#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"
#include <unistd.h>
#define NUM_THREADS  5

typedef struct {
    pthread_mutex_t *mutex;
    const char *msg;
} Data;

void *PrintHello(void *arg)
{
  Data *d = (Data *) arg;

  printf("thread run[name:%s]\n", d->msg);

  sleep(4);

  printf("thread end\n");

  free(d);
  pthread_exit(NULL);
}

void run(pthread_mutex_t *mutex, const char *msg) {
    Data *d = (Data *) malloc(sizeof(Data));
    d->msg = msg;
    d->mutex = mutex;

    pthread_t t;
    pthread_create(&t, NULL, PrintHello, (void *)d);
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    printf("main start\n");

    static pthread_mutex_t mutex;

    run(&mutex, "A");
    sleep(5);

    printf("main end\n");
    pthread_exit(NULL);
}
