#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    printf("main 1\n");

    char buf[128];
    printf("%s\n", buf);
    int len = strlen(buf);
    sprintf(buf + len, "aaaa%s", "bbb");
    printf("%s\n", buf);

    printf("main 2\n");
}
