#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "HelloWorld.h"

jobjectArray strAry2jObjAry(JNIEnv *env, char *src, const int cnt, const int len) {
  jclass cls = env->FindClass("java/lang/String");
  jobjectArray jarray = env->NewObjectArray(cnt, cls, NULL);

  for (int i = 0; i < cnt; i++) {
    char *s = src + len * i;
    printf("%s\n", s);
    jstring string = env->NewStringUTF(s);
    env->SetObjectArrayElement(jarray, i, string);
  }

  return jarray;
}

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
    printf("main 1\n");

    const int CNT = 3;
    const int LEN = 10;
    char test[CNT][LEN] = {
      "aaaaa",
      "bbb",
      "ccccccccc"
    };

    jobjectArray jarray = strAry2jObjAry(env, (char*)test, CNT, LEN);

    jclass cls = env->FindClass("HelloWorld");
    jfieldID fieldID5 = env->GetStaticFieldID(cls, "mdnNormal", "[Ljava/lang/String;");
    env->SetStaticObjectField(cls, fieldID5, jarray);

    printf("main 2\n");
}
