#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"
#include <unistd.h>
#include "asm-generic/errno-base.h"
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

  printf("thread end[name:%s]\n", d->msg);

  free(d);
  pthread_exit(NULL);
}

void run(pthread_mutex_t *mutex, const char *msg) {
    Data *d = (Data *) malloc(sizeof(Data));
    d->msg = msg;
    d->mutex = mutex;

    switch (pthread_mutex_trylock(mutex)) {
      case EINVAL:
        printf("thread EINVAL[name:%s]\n", msg);
        return;
      case EBUSY:
        printf("thread EBUSY[name:%s]\n", msg);
        return;
    }
    pthread_t t;
    pthread_create(&t, NULL, PrintHello, (void *)d);
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    printf("main start\n");

    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    run(&mutex, "A");
    sleep(1);
    run(&mutex, "B");
    sleep(1);
    run(&mutex, "C");
    sleep(1);
    run(&mutex, "D");
    sleep(1);
    run(&mutex, "E");
    sleep(1);
    run(&mutex, "F");
    sleep(1);
    run(&mutex, "G");
    sleep(1);
    run(&mutex, "H");
    sleep(1);
    run(&mutex, "I");
    sleep(1);
    sleep(1);

    printf("main end\n");
    pthread_exit(NULL);
}
