#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"
#include <unistd.h>
#include "asm-generic/errno-base.h"
#define NUM_THREADS  5

typedef struct {
    const char *msg;
    const bool *busy;
} Data;

void thread_cleanup(void *data_) {
  Data *d = (Data *)data_;
  printf("thread cleanup[name:%s]\n", d->msg);
  free(d);
}

void *PrintHello(void *data_)
{
  pthread_cleanup_push(thread_cleanup, data_);
  Data *d = (Data *) data_;

  printf("thread run[name:%s]\n", d->msg);

  sleep(4);

  printf("thread end[name:%s]\n", d->msg);

  pthread_cleanup_pop(1);
  pthread_exit(NULL);
}

void run(bool *busy, const char *msg) {
    Data *d = (Data *) malloc(sizeof(Data));
    d->msg = msg;
    d->busy = busy;

    pthread_t t;
    pthread_create(&t, NULL, PrintHello, (void *)d);
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    printf("main start\n");

    static bool busy = false;

    run(&busy, "A");
    sleep(1);
    run(&busy, "B");
    sleep(1);
    run(&busy, "C");
    sleep(1);
    run(&busy, "D");
    sleep(1);
    run(&busy, "E");
    sleep(1);
    run(&busy, "F");
    sleep(1);
    run(&busy, "G");
    sleep(1);
    run(&busy, "H");
    sleep(1);
    run(&busy, "I");
    sleep(1);
    sleep(1);

    printf("main end\n");
    pthread_exit(NULL);
}
