#!/bin/sh

# Linux 2.6.32-358.el6.x86_64
# gcc 4.4.7
# openjdk 1.7.0

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. &&\
javac -g HelloWorld.java &&\
javah HelloWorld &&\
export JAVA_HOME=/usr/lib/jvm/java-8-oracle &&\
g++ -shared -fPIC -g -O0 -I $JAVA_HOME/include -I $JAVA_HOME/include/linux libHelloWorld.cpp -o libHelloWorld.so &&\
java HelloWorld
